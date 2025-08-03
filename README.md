# 🧩 KF1

## 📖 Description

**KFS_1** est le premier projet du cursus Kernel From Scratch de 42. L'objectif est de créer un noyau minimal en **C** et **ASM**, capable de démarrer via GRUB et d'afficher du texte à l'écran. Ce projet initie aux bases du développement bas niveau et de l'architecture système.

---

## 🎯 Objectifs du projet

- Boot via **GRUB** (Multiboot)
- Initialisation du kernel en **ASM** et appel de `main()` en **C**
- Affichage à l'écran (mode texte)
- Affichage de `42` comme preuve de fonctionnement
- Compilation et linkage manuels sans dépendances système
- Image bootable **≤ 10 Mo**

---

## 🔧 Technologies prévues

- **Langage principal :** C (freestanding)
- **Bootloader :** ASM (nasm)
- **Compilation :** gcc, nasm
- **Émulation :** qemu ou KVM (selon préférence)
- **Architecture :** x86 (i386)

---

## 📁 Structure prévue
``` 
KFS_1/
├── Makefile       
├── linker.ld      
├── boot/
│   └── boot.asm
├── src/
│   └── kernel.c
├── include/
│   └── kernel.h
└── img/
    └── kfs.img
```
