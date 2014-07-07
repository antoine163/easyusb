//! \file **********************************************************************
//!
//! \brief Header de EasyUsb pour le c.
//!
//! - Compilateur		: GCC
//!
//! \author Maleyrie Antoine
//! \version 0.1
//! \date 07.07.2014
//!
//! ****************************************************************************

#ifndef EASYUSB_H
#define EASYUSB_H

//! \addtogroup ipc C
//! \brief Implementation en C de EasyUsb.
//!
//! Voici un exemple simple:
//! \code
//!	#include "easyusb.h"
//!
//! //Identifiant USB du Vendeur.
//! #define  VID		0xab34
//! //Identifiant de produit.
//! #define  PID		0x78b1
//! 
//! int main()
//! {
//! 	//Un buffer de données
//! 	unsigned char bufusb[32];
//!		//Pointeur sur le device.
//!		usb_device* device = NULL;
//! 	
//!		//Initialisation de l'API
//!		if(!usb_init())
//! 		return -1;
//!     
//! 	//...
//! 
//! 	//Connexion au device usb.
//!		device = usb_connect(VID, PID);
//! 	if(device == NULL)
//! 		return -1;
//!     	
//! 	//...
//! 
//! 	//Lecture de 32 octets.
//! 	if(usb_read(device, bufusb, 32) == -1)
//! 		return -1;
//! 		
//! 	//...
//! 		
//! 	//Écriture de 16 octets.
//! 	if(usb_write(device, bufusb, 16) == -1)
//! 		return -1;
//! 		
//! 	//...
//! 		
//! 	//Déconnexion du device.
//! 	usb_disconnect(device);
//! 		
//! 	//...
//! 		
//! 	//Fermeture de l'API.
//! 	usb_close();
//! 		
//! 	//...
//!     
//! 	return 0;
//! }
//! \endcode
//!
//! @{

//_____ I N C L U D E S ________________________________________________________
#include <libusb-1.0/libusb.h>

//_____ T Y P E D E F __________________________________________________________
typedef usb_device libusb_device_handle;

//_____ P R O T O T Y P E S ____________________________________________________

//_____ F U N C T I O N ________________________________________________________
//! \brief Permet d'initialiser l'api.
//! \return 0 si tout s'est bien passer, sinon -1.
int usb_init();

//! \brief Permet de fermer l'api.
void usb_close();

//! \brief Permet de se connecter un périphérie usb.
//!
//! \param vendor_id est l'id du vendeur.
//! \param product_id est l'id du produit.
//! \return NULL si problème, sinon un pointeur vair le devise.
usb_device* usb_connect(uint16_t vendor_id, uint16_t product_id);

//! \brief Permet de se déconnecter du périphérie usb.
//! \param device pointeur ver le device. Après cette fonction device vaudra \b
//! NULL.
void usb_disconnect(usb_device* device);

//! \brief Reset le périphérie.
//!
//! Utile si la connections a réussit.
//! \param device pointeur ver le device.
//! \return 0 si tout s'est bien passer, sinon -1.
int usb_reset(usb_device* device);

//! \brief Écrie des données ver le périphérie.
//!
//! \param device pointeur ver le device.
//! \param data les données à écrire.
//! \param size le nombre de données à écrire.
//! \return -1 si il ces produit un problème, sinon le nombre de données qui a été transmis.
int usb_write(usb_device* device, unsigned char data[], int size);

//! \brief Lire des données provenant du périphérie.
//!
//! \param device pointeur ver le device.
//! \param data là ou les données lu serons écrite.
//! \param size la taille du buffer data en octet.
//! \return -1 si il ces produit un problème, sinon le nombre de données qui a été lue.
int usb_read(usb_device* device, unsigned char data[], int size);

#endif // EASYUSB_H
