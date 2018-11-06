#include "ligne_commande.h"
#include <stdio.h> // perror(3), printf(3)
#include <string.h>
#include <unistd.h> // fork(2), getpid(2)
#include <sys/types.h> // getpid(2), wait(2)
#include <sys/wait.h> // wait(2)
#include <stdlib.h>

#include "ligne_commande.h"

int commandes_internes(char**);

int main(void) {
  char** commande;
  pid_t pid;
  int etat;

  while(1)
  {
    commande=lis_ligne();

    if (fin_de_fichier(commande))
     {
      fprintf(stdout,"fin de programme\n");
      return 0;
    }
    else
    {
      if(!ligne_vide(commande))
      {
        if(!commandes_internes(commande))
        {
          pid=fork();
          if(pid==0)
          {
            if(execvp(commande[0],commande)==-1)
                fprintf(stdout, "Erreur :commande incorrecte\n");
           return 0;
          }
          wait(&etat);
        }

      }
    }
  }
  return 0;
}

  int commandes_internes(char** cmd)
  {
    if(!strcmp(cmd[0],"exit"))
    {
      fprintf(stdout,"fin du programme\n");
      exit(0);
    }
    if(!strcmp(cmd[0],"cd"))
    {
      if(cmd[1])
        chdir(cmd[1]);
      return 1;
    }
    return 0;
  }
