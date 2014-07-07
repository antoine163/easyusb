//! \file **********************************************************************
//!
//! \brief Implémentation de EasyUsb pour le c++.
//!
//! - Compilateur		: GCC
//!
//! \author Maleyrie Antoine
//! \version 0.3
//! \date 26 Août 2011
//!
//! ****************************************************************************

//_____ I N C L U D E S ________________________________________________________
#include <iostream>
#include "easyusb.h"

//_____ M A C R O S ____________________________________________________________

//_____ I M P L E M E N T A T I O N S __________________________________________

EasyUsb::EasyUsb() : _ctx(0), _device(0)
{
	// Création d'un contexte pour utiliser l'usb.
	if(libusb_init(&_ctx) != 0)
	{
		std::cerr << "EasyUsb::EasyUsb libusb initialisation failed." << std::endl;
		libusb_set_debug(_ctx, 3);
	}
}

EasyUsb::~EasyUsb()
{
	disconnect();
	libusb_exit(_ctx);
}

bool EasyUsb::connect(uint16_t vendor_id, uint16_t product_id)
{
	//On déconnecté si il est déjà connecter.
	disconnect();

	//Récupéré le device lier aux ids.
	_device = libusb_open_device_with_vid_pid(_ctx, vendor_id, product_id);
	//Si erreur ou si le device n'a pas été trouver.
	if(_device == 0)
	{
		std::cerr << "EasyUsb::connect The device is not found or error." << std::endl;
		return false;
	}

	//Vérifie si un driver n'est pas déjà charger.
	if(libusb_kernel_driver_active(_device, 0) == 1)
	{
		//On détache le driver.
		libusb_detach_kernel_driver(_device, 0);
	}

	//Reset le périphérie.
	reset();

	return true;
}

void EasyUsb::disconnect()
{
	//Si il existe un périphérie.
	if(_device != 0)
	{
		//Reset le périphérie.
		reset();

		//Met fin au périphérie.
		libusb_close(_device);
		_device = 0;
	}
}

bool EasyUsb::reset()
{
	if(libusb_reset_device(_device) != 0)
	{
		std::cerr << "EasyUsb::reset Failed the reset device." << std::endl;
		return false;
	}

	return true;
}

int EasyUsb::write(unsigned char data[], int size)
{
	//Si il n'existe pas de périphérie.
	if(_device == 0)
	{
		std::cerr << "EasyUsb::write No device for write." << std::endl;
		return -1;
	}

	//On demande à communiquer.
	if(libusb_claim_interface(_device, 1) != 0)
	{
		//On ce déconnecte si erreur.
		disconnect();
		std::cerr << "EasyUsb::write The claim has failed." << std::endl;
		return -1;
	}

	//Écriture des données.
	int nwrite = 0;
	if(libusb_bulk_transfer(_device, (2|LIBUSB_ENDPOINT_OUT), data, size, &nwrite, 0) != 0)
	{
		std::cerr << "EasyUsb::write Error has write the data." << std::endl;
		return -1;
	}

	//On ne veut plus communiquer.
	if(libusb_release_interface(_device, 1) != 0)
	{
		std::cerr << "EasyUsb::write The release has failed." << std::endl;
		return -1;
	}

	return nwrite;
}

int EasyUsb::read(unsigned char data[], int size)
{
	//Si il n'existe pas de périphérie.
	if(_device == 0)
	{
		std::cerr << "EasyUsb::read No device for read." << std::endl;
		return -1;
	}

	//On demande à communiquer.
	if(libusb_claim_interface(_device, 1) != 0)
	{
		//On ce déconnecte si erreur.
		disconnect();
		std::cerr << "EasyUsb::read The claim has failed." << std::endl;
		return -1;
	}

	//Lecture des données.
	int nread = 0;
	if(libusb_bulk_transfer(_device, (1|LIBUSB_ENDPOINT_IN), data, sizeData, &nread, 0) != 0)
	{
		std::cerr << "EasyUsb::read Error has read the data." << std::endl;
		return -1;
	}

	//On ne veut plus communiquer.
	if(libusb_release_interface(_device, 1) != 0)
	{
		std::cerr << "EasyUsb::read The release has failed." << std::endl;
		return -1;
	}

	return nread;
}

