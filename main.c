#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>/* condition */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <sys/mman.h>

extern int bootloader(void);

unsigned char nazi_crypt(unsigned char byte, unsigned char prev_byte)
{
    byte ^= prev_byte;
    byte += 88;

}

int main()
{

    bootloader();
    FILE *fp = fopen("a.out", "rb");
    printf("\nlmao\n");

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    unsigned char *elf = malloc(size);
    fread(elf, 1, size, fp);

    Elf64_Ehdr *hdr = (Elf64_Ehdr *)elf;

    // printf("ELF section offset: %lx\n", hdr->e_shoff);
    // printf("ELF section count: %ld\n", hdr->e_shnum);
    // printf("ELF section names index: %ld\n", hdr->e_shstrndx);

    // e = elf, sh = section header, ent = entry, size = size, e_shentsize = elf's section header size
    Elf64_Shdr *shdr = (Elf64_Shdr *)(elf + hdr->e_shoff); /* assumes hdr->e_shentsize == (sizeof(Elf64_Shdr))  */

    
    uint32_t ei_class = *(uint32_t *)(elf + EI_CLASS);
    // if (elf[EI_MAG0] != ELFMAG0  || elf[EI_MAG1] != ELFMAG1 ||
    //     elf[EI_MAG2] != ELFMAG2 || elf[EI_MAG3] != ELFMAG3)
    //     {
    //         printf("The file isn't a ELF compliant file\n");
    //         return;
    //     }

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
    // elf 0x0 - ...
    // ...
    // liste des noms - 0x1000
    // 0x1000: ""
    // 0x1001: ".plt"
    // ...
    // sh_name = 1

    // e_shstrndx -> la section e_shstrndx c'est les noms
    // sh_offset => le contenue la section est a l'emplacement sh_offset
    // sh_name -> apartir des noms, je suis o l'offset sh_name

    // on recupere l'emplacement des noms
    char *sec_names = (elf + shdr[hdr->e_shstrndx].sh_offset);

    Elf64_Phdr *phdr = elf + hdr->e_phoff;

/* condition */
    for (int i = 0; i < hdr->e_shnum; i++)
    {
        if (strcmp(sec_names + shdr[i].sh_name, ".text") == 0)
        {
            shdr[i].sh_flags |= SHF_WRITE;
            char *ptr = elf + shdr[i].sh_offset;
            const char *txt_sectn = (const char *)sec_names + shdr[i].sh_name;
            char prev_byte = 0;
            for (int y = 0; y < shdr[i].sh_size; y++)
            {
                char tmp = ptr[y];
                ptr[y] = nazi_crypt(ptr[y], prev_byte);
                prev_byte = tmp;
            }
            // We iterate in the program headers and we find the section that contains our .text and give ourselves permission to write
            for(int y = 0; y < hdr->e_phnum; y++) {
                if(phdr[y].p_vaddr <= shdr[i].sh_addr && phdr[y].p_vaddr + phdr[y].p_memsz >= shdr[i].sh_addr) {
                    phdr[y].p_flags |= PF_W;
                }
            }
            
            break;
        }
    }
    ///Elf64_Phdr *phdr = elf + hdr->e_phoff;
    //hdr->e_phoff = ...;
    //hdr->e_phnum += 1;
    //
    //real_main = hdr->e_entry;

    //hdr->e_entry = bootloader; 

    FILE *outputfp = fopen("couilles", "wb");
    
    fwrite(elf, 1, size, outputfp);
    fclose(outputfp);
    // void *mapped_file = mmap(NULL, hdr->e_phnum * sizeof(Elf64_Phdr), PROT_READ | PROT_WRITE, MAP_PRIVATE, fileno(fp), 0);
    // if (mapped_file == MAP_FAILED)
    // {
    //     perror("Error mapping file");
    //     fclose(fp);
    //     return;
    // }    
    
    
    //Elf64_Shdr *text_section = &shdr[(int)text_section - hdr->e_shstrndx]; 
    //off_t txtoff = text_section->sh_offset;
    // for (int i = 0; i < hdr->e_phnum; i++)
    // {
    //     if(phdr[i].p_type == PT_LOAD && (phdr[i].p_flags & PF_X)) {
    //         char *txt_start = elf + phdr[i].p_offset;
    //         //size_t txt_size = phdr[i].p_filesz;

    //         printf("Contents of .text section:\n");
    //         fwrite(txt_start, 1, 10, stdout);
    //         // munmap(mapped_file,hdr->e_phnum * sizeof(Elf64_Phdr));
    //         //fclose(fp);
    //         //return;
    //     }
    // }
     
    for (int i = 0; i < hdr->e_shnum; i++) {
        printf("name: %s offset: %lx banderas: %lx, res: %lx\n", sec_names + shdr[i].sh_name, shdr[i].sh_offset, shdr[i].sh_flags, shdr[i].sh_flags, (SHF_ALLOC | SHF_EXECINSTR));
        if ((shdr[i].sh_flags & (SHF_ALLOC | SHF_EXECINSTR)) == (SHF_ALLOC | SHF_EXECINSTR))
        {
            printf("wow jb found :00000 \n");
            
        }
    }
}