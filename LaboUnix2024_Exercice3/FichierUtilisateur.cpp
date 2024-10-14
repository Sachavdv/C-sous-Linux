#include "FichierUtilisateur.h"

int estPresent(const char* nom)
{
  UTILISATEUR user;
  int fd = 0;
  int position = 1;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) != -1)
  {
    while(read(fd, &user, sizeof(UTILISATEUR)) == sizeof(UTILISATEUR))
    {
      if(strcmp(user.nom, nom) == 0)
      {
        close(fd),
        return position;
      }
      position++;
    }
    close(fd);
  }
  printf("erreur lors de l ouverture du fichier");
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////
int hash(const char* motDePasse)
{
    int asciiValue;  
    int hashValue = 1;  
    int i = 0;      

    while (motDePasse[i] != '\0')
    {
        asciiValue = (int)motDePasse[i]; 
        hashValue = hashValue * asciiValue;          
        i++;
        hashValue++;
    }

    hashValue = hashValue % 97;

    return hashValue; 
}

////////////////////////////////////////////////////////////////////////////////////
void ajouteUtilisateur(const char* nom, const char* motDePasse)
{
  UTILISATEUR add;
  int fd;
  if((fd = open(FICHIER_UTILISATEURS, O_WRONLY | O_CREAT | O_APPEND)) == -1)
  {
    printf("erreur lors de l'ouverture du FichierUtilisateur");
    return -1;
  }

  strcpy(add.nom, nom);
  add.hash = hash(motDePasse);
  write(fd, &add, sizeof(UTILISATEUR));
  close(fd);

}

////////////////////////////////////////////////////////////////////////////////////
int verifieMotDePasse(int pos, const char* motDePasse)
{

  UTILISATEUR cmpMdp;
  int fd;
  int ret;

  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) != -1)
  {
    lseek(fd, sizeof(UTILISATEUR) * (pos - 1), SEEK_CUR);
    read(ld, &cmpMdp, sizeof(UTILISATEUR));
    ret = hash(motDePasse);
    if(ret == cmpMdp.hash)
    {
      close(fd);
      return 1; 
    }

    close(fd);
    return 0;
  }
  printf("erreur lors de l'ouverture du fichier");
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////
int listeUtilisateurs(UTILISATEUR *vecteur) // le vecteur doit etre suffisamment grand
{
  int i = 0;
  UTILISATEUR liste;
  int fd;
  if((fd = open(FICHIER_UTILISATEURS, O_RDONLY)) != -1)
  {
    while(read(fd, &liste, sizeof(UTILISATEUR)) == sizeof(UTILISATEUR))
    {
      vecteur[i] = liste;
      i++;
    }
    close(fd);
    return i;
  }
  printf("erreur lors de l'ouverture du fichier");
  return -1;
}