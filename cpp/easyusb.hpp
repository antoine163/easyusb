//! \file **********************************************************************
//!
//! \brief Header de EasyUsb pour le c++.
//!
//! - Compilateur		: GCC 
//!
//! \author Maleyrie Antoine
//! \version 0.3
//! \date 26 Août 2011
//!
//! ****************************************************************************

#ifndef EASYUSB_H
#define EASYUSB_H

//! \addtogroup ipcpp C++
//! \brief Implementation en C++ de EasyUsb.
//!
//! Voici un exemple simple:
//! \code
//!	#include "easyusb.hpp"
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
//! 	
//!		//Une classe usb
//!		EasyUsb usb;
//!     
//! 	//...
//! 
//! 	//Connexion au device usb.
//! 	if(!usb.connect(VID, PID))
//! 		return -1;
//!     	
//! 	//...
//! 
//! 	//Lecture de 32 octets.
//! 	if(usb.read(bufusb, 32) == -1)
//! 		return -1;
//! 		
//! 	//...
//! 		
//! 	//Écriture de 16 octets.
//! 	if(usb.write(bufusb, 16) == -1)
//! 		return -1;
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

//_____ P R O T O T Y P E S ____________________________________________________

//_____ C L A S S ______________________________________________________________

//! \brief Classe représentent un périphérie usb.
//!
//! \note Les méthode \ref write() et read() sont des fonction bloquent.
//! \attention Pour le moment, il est déconseiller de crée plusieurs instances de
//! cette classe pour accéder à plusieurs périphéries.
//! \todo Tester avec plusieurs instance et plusieurs périphérie.
class EasyUsb
{
	public:
		//! \brief Constructeur.
		EasyUsb();
		//! \brief Déstructure.
		~EasyUsb();

		//! \brief Permet de se connecter un périphérie usb.
		//!
		//! \param vendor_id est l'id du vendeur.
		//! \param product_id est l'id du produit.
		//! \return true si tout s'est bien passer, sinon false.
		bool connect(uint16_t vendor_id, uint16_t product_id);

		//! \brief Permet de se déconnecter du périphérie usb.
		void disconnect();

		//! \brief Reset le périphérie.
		//!
		//! Utile si la connections a réussit.
		//! \return true si tout s'est bien passer, sinon false.
		bool reset();

		//! \brief Écrie des données ver le périphérie.
		//!
		//! \param data les données à écrire.
		//! \param size le nombre de données à écrire.
		//! \return -1 si il ces produit un problème, sinon le nombre de données qui a été transmis.
		int write(unsigned char data[], int size);

		//! \brief Lire des données provenant du périphérie.
		//!
		//! \param data là ou les données lu serons écrite.
		//! \param size la taille du buffer data en octet.
		//! \return -1 si il ces produit un problème, sinon le nombre de données qui a été lue.
		int read(unsigned char data[], int size);

	private:
		//Un contexte usb.
		libusb_context *_ctx;
		//Le périphérie usb.
    	libusb_device_handle *_device;
};

//! @} //C++

#endif // EASYUSB_H
