//! \file **********************************************************************
//!
//! \brief Implémentation de EasyUsb pour le c.
//!
//! - Compilateur		: GCC
//!
//! \author Maleyrie Antoine
//! \version 0.1
//! \date 07.07.2014
//!
//! ****************************************************************************

//_____ I N C L U D E S ________________________________________________________
#include <stdio.h>
#include "easyusb.h"

//_____ M A C R O S ____________________________________________________________

//_____ V A R I A B L E ________________________________________________________
libusb_context *_usbctx;

//_____ I M P L E M E N T A T I O N S __________________________________________
int usb_init()
{
	// Création d'un contexte pour utiliser l'usb.
	if(libusb_init(&_usbctx) != 0)
	{
		fprintf(stderr, "usb_init: libusb initialisation failed.\n");
		libusb_set_debug(_usbctx, 3);
		return -1;
	}
	
	return 0;
}

void usb_close()
{
	libusb_exit(_usbctx);
}

usb_device* usb_connect(uint16_t vendor_id, uint16_t product_id)
{
	//Récupéré le device lier aux ids.
	usb_device device* = libusb_open_device_with_vid_pid(_usbctx, vendor_id, product_id);
	//Si erreur ou si le device n'a pas été trouver.
	if(device == NULL)
	{
		fprintf(stderr, "usb_connect: The device is not found or error.\n");
		return NULL;
	}

	//Vérifie si un driver n'est pas déjà charger.
	if(libusb_kernel_driver_active(device, 0) == 1)
	{
		//On détache le driver.
		libusb_detach_kernel_driver(device, 0);
	}

	//Reset le périphérie.
	usb_reset(device);

	return device;
}

void usb_disconnect(usb_device* device)
{
	//Reset le périphérie.
	usb_reset(device);

	//Met fin au périphérie.
	libusb_close(device);
	device = NULL;
}

int usb_reset(usb_device* device)
{
	if(libusb_reset_device(device) != 0)
	{
		fprintf(stderr, "usb_reset: Failed the reset device.\n");
		return -1;
	}

	return 0;
}

int usb_write(usb_device* device, unsigned char data[], int size)
{
	//On demande à communiquer.
	if(libusb_claim_interface(device, 1) != 0)
	{
		//On ce déconnecte si erreur.
		usb_disconnect(device);
		fprintf(stderr, "usb_write: The claim has failed.\n");
		return -1;
	}

	//Écriture des données.
	int nwrite = 0;
	if(libusb_bulk_transfer(device, (2|LIBUSB_ENDPOINT_OUT), data, size, &nwrite, 0) != 0)
	{
		fprintf(stderr, "usb_write: Error has write the data.\n");
		return -1;
	}

	//On ne veut plus communiquer.
	if(libusb_release_interface(device, 1) != 0)
	{
		fprintf(stderr, "usb_write: The release has failed.\n");
		return -1;
	}

	return nwrite;
}

int usb_read(usb_device* device, unsigned char data[], int size)
{
	//On demande à communiquer.
	if(libusb_claim_interface(device, 1) != 0)
	{
		//On ce déconnecte si erreur.
		usb_disconnect(device);
		fprintf(stderr, "usb_read: The claim has failed.\n");
		return -1;
	}

	//Lecture des données.
	int nread = 0;
	if(libusb_bulk_transfer(device, (1|LIBUSB_ENDPOINT_IN), data, size, &nread, 0) != 0)
	{
		fprintf(stderr, "usb_read: Error has read the data.\n");
		return -1;
	}

	//On ne veut plus communiquer.
	if(libusb_release_interface(device, 1) != 0)
	{
		fprintf(stderr, "usb_read: The release has failed.\n");
		return -1;
	}

	return nread;
}

