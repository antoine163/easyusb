/*Fichier conçu pour la génération de la documentation automatique avec
* Doxygen.
*/
//! \file **********************************************************************
//!
//! \brief Header pour une utilisation facile de l'usb.
//!
//! - Compilateur		: GCC
//!
//! \author Maleyrie Antoine : antoine.maleyrie@gmail.com
//! \version 0.2
//! \date 26 Août 2011
//!
//! ****************************************************************************

//! \mainpage EasyUsb
//! EasyUsb est une mini bibliothèque s'appuyant sur la libusb1.0, elle permet une
//! manipulation basique mais simple de périphérie usb.
//!
//! \see http://www.libusb.org/

/*
*	Copyright © 2011 - Antoine Maleyrie.
*/

#ifndef EASYUSB_H
#define EASYUSB_H

//_____ I N C L U D E S ________________________________________________________
#include <libusb-1.0/libusb.h>

//_____ P R O T O T Y P E S ____________________________________________________

//_____ C L A S S ______________________________________________________________

//! \brief Classe permettant d'utiliser un périphérie usb facilement est simplement.
//!
//! \note les méthode \ref write() et read() sont des fonction bloquent (synchrone).
//! \attention Cette classe n'est pas une classe singletone, mais, ceci dit, aucun test a été fais avec plusieurs instance, il et donc déconseiller de créés plusieurs instance ...
//!
//! \code
//! //Identifiant USB du Vendeur.
//! #define  VID		0xab34
//! //Identifiant de produit.
//! #define  PID		0x78b1
//! 
//! int main()
//! {
//! 	//Un buffer de données
//! 	unsigned char buffusb[32];
//! 	
//!		//Une classe usb
//!		EasyUsb usb;
//!     
//! 	//...
//! 
//! 	//Connexion au device usb.
//! 	if(!usb.connect(VID, PID))
//! 		return 1;
//!     	
//! 	//...
//! 
//! 	//lecture de données
//! 	if(!usb.read(buffusb, 32))
//! 		return 1;
//! 		
//! 	//...
//! 		
//! 	//Écriture de données
//! 	if(!usb.write(buffusb, 16))
//! 		return 1;
//! 		
//! 	//...
//!     
//! 	return 0;
//! }
//! \endcode


class EasyUsb
{
	public:
		//! \brief Constructeur.
		EasyUsb();
		//! \brief Déstructure.
		~EasyUsb();

		//! \brief Permet de se connecter un périphérie usb.
		//!
		//! \param vendor_id est id du vendeur.
		//! \param product_id est id du produit.
		//! \return true si tout s'est bien passer, sinon false.
		bool connect(uint16_t vendor_id, uint16_t product_id);

		//! \brief Permet de se déconnecter du périphérie usb.
		void disconnect(void);

		//! \brief Reset le périphérie.
		//!
		//! Utile si la connections a réussit.
		//! \return true si tout s'est bien passer, sinon false.
		bool reset(void);

		//! \brief Écrie des données vair le périphérie.
		//!
		//! \param data les données a écrire.
		//! \param length le nombre de données.
		//! \return true si tout s'est bien passer, sinon false.
		bool write(unsigned char data[], int length);

		//! \brief Lire des données sur provenant du périphérie.
		//!
		//! \param data les données a écrire.
		//! \param length le nombre de données.
		//! \return true si tout s'est bien passer, sinon false.
		bool read(unsigned char data[], int length);

	private:
		//Un contexte usb.
		libusb_context *_ctx;
		//Le périphérie usb.
    	libusb_device_handle *_device;
};

#endif // EASYUSB_H
