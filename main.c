#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <elf.h>



int main()
{
    FILE *fp = fopen("a.out", "rb");

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    unsigned char *elf = malloc(size);
    fread(elf, 1, size, fp);

    Elf64_Ehdr *hdr = (Elf64_Ehdr *)elf;

    printf("ELF section offset: %lx\n", hdr->e_shoff);
    printf("ELF section count: %ld\n", hdr->e_shnum);
    printf("ELF section names index: %ld\n", hdr->e_shstrndx);

    // e = elf, sh = section header, ent = entry, size = size, e_shentsize = elf's section header size
    Elf64_Shdr *shdr = (Elf64_Shdr *)(elf + hdr->e_shoff); /* assumes hdr->e_shentsize == (sizeof(Elf64_Shdr))  */

    
    uint32_t ei_class = *(uint32_t *)(elf + EI_CLASS);
    printf("ELF confirmation: %u\n", elf[0x32]);


    //     switch(elf[4]) {
    //     case ELFCLASSNONE:
    //         printf("Invalid class\n");
    //         break;
    //     case ELFCLASS32:
    //         printf("32-bit objects\n");
    //         break;
    //     case ELFCLASS64:
    //         printf("64-bit objects\n");
    //         break;
    //     default:
    //         printf("Unknown class\n");
    // }
    // // elf 0x0 - ...
    // // ...
    // // liste des noms - 0x1000
    // // 0x1000: ""
    // // 0x1001: ".plt"
    // // ...
    // // sh_name = 1

    // // e_shstrndx -> la section e_shstrndx c'est les noms
    // // sh_offset => le contenue la section est a l'emplacement sh_offset
    // // sh_name -> apartir des noms, je suis o l'offset sh_name

    // // on recupere l'emplacement des noms
    // char *sec_names = (elf + shdr[hdr->e_shstrndx].sh_offset);

    // for (int i = 0; i < hdr->e_shnum; i++) {
    //     printf("section %d sh_name: %d name: %s offset: %lx\n",i, shdr[i].sh_name, sec_names + shdr[i].sh_name, shdr[i].sh_offset);
    // }
}