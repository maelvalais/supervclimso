Ce dépôt contient les sources du programme de supervision `supervclimso` lié à la machine "SPV1" du système CLIMSO (coronographes du Pic du Midi). 

Plusieurs versions sont disponibles sous forme de "[branches](https://github.com/mael65/supervclimso/branches)". Les problèmes à résoudre sur le programme sont contenus dans l'onglet "[Issues](https://github.com/mael65/supervclimso/issues)."

Le système CLIMSO est composé de 3 autres programmes : [`cameroa`](https://github.com/mael65/cameroa), [`terminoa`](https://github.com/mael65/terminoa) et [`roboa`](https://github.com/mael65/roboa). `supervclimso` gère l'ensemble des procédures d'acquisition et de mouvements des roues à filtres et platines. Les schémas des architectures matérielles (y compris le réseau) et logicielles sont disponibles sur le site de [climso.fr](http://www.climso.fr/index.php/fr/climso).

Note: J'ai mis en ligne ces sources en retirant toute partie posant problème (certificats SSL, adresses privées internes, ports...). J'espère aussi que David Romeuf ne m'en voudra pas d'avoir copié son travail sur un espace de développement public, qui permettra peut-être de simplifier la maintenance de ce logiciel complexe.

# Avant de compiler et utiliser `supervclimso`

## Installer les librairies nécessaires

	yum install gcc gcc-c++ qt3 qt3-devel kdelibs3 kdelibs3-devel autoconf automake libtool cfitsio cfitsio-devel

Et aussi éventuellement `git` pour récupérer les sources depuis le dépôt (il est aussi possible de télécharger un .zip directement) :

	yum install git

## Ajuster les paramètres réseau
Il faut que la machine sur laquelle tourne `supervclimso` ait l'adresse `192.168.6.1` et que le fichier `/etc/hosts` contienne les liens entre les noms `cameroa-1.pic.obs-mip.fr` et `192.168.6.20` par exemple. Si ça n'est pas le cas, il faut les y ajouter.

# Compiler `supervclimso`

On récupère les sources (en `.zip` ou grace à la commande `git clone git@github.com:mael65/supervclimso.git`). Depuis le dossier du projet `supervclimso/`, lancez les commandes :

	./configure
	make

L'exécutable créé est `supervclimso/src/supervclimso`. Il faudra copier cet exécutable dans l'étape suivante.

# Installer et lancer `supervclimso`

Il faut récupérer [l'archive du dossier `/SupervCLIMSO`](https://dl.dropboxusercontent.com/u/41771140/climso/SupervCLIMSO.zip) à mettre à la racine du système et appliquer les droits appropriés. Le dossier `/SupervCLIMSO` doit comprendre au moins :

- `lancement-supervclimso`
- le dossier `ssl/` (avec 3 fichiers .pem dedans)
- le dossier `scripts/` (avec tous les fichiers cmd.* dedans)
- le dossier `outils/`
- le dossier `tmp/`
- `SupervCLIMSO_Consignes.dat` qui contient les consignes (les températures des caméras...)
- `supervclimso` (n'y sera pas au début, il faut l'ajouter après avoir compilé)

L'exécutable `supervclimso` doit être copié depuis le dossier où vous avez compilé le projet cameroa. Dans le dossier de compilation `supervclimso/`, il se trouve dans `supervclimso/src/supervclimso`. Copiez-le donc dans `/SupervCLIMSO`.

Il suffit enfin de lancer en tappant `/SupervCLIMSO/lancement-supervclimso`.
	

# Modifications apportées vis à vis du source d'origine
Une [page du wiki](https://github.com/mael65/projet-climso/wiki/Ce-que-j%27ai-fait-pour-compiler-supervclimso) permet de comprendre quelles changements ont été faits pour rendre la compilation possible.
