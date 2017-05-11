# LIBHASH

La libhash est une librairie écrite en C, qui comme son nom l'indique, permet la création de hash.
Elle a pour but l'amélioration d'une recherche traditionnelle en C sur les listes qui généralement 
consistent à itérer sur chaque élément et comparer un champ avec notre recherche.
Ce qui, sur de grosses listes, prend un temp fou.


## Introduction

Grâce à cette librairie vous pourrez implémenter des hash très facilement.
Ci-dessous vous trouverez les spécificités et les fonctions que vous pourrez utiliser sur 
votre hash mais pour l'heure un petit débrif s'impose.

### Fonctionnement

Pour rappel, un hash est une sorte de tableau qui retourne des valeurs en fonction des clefs qu'on
leur passe et non des index. La solution la plus simple est donc de convertir la clef en index grâce à un algorithme avec lequel
il nous sera facile de retouver une valeur qui aura été ajoutée dans notre hash.

Prenons un exemple:

Imaginons que nous voulions sauvegarder une clef "chat" avec pour valeur "Felix".
Quand vous enrengistrerez "Felix" la clef "chat" va être tranformée en index avec un algorithme qui 
pourrait additionner chaque valeur ascii de la clef chat % la taille du tableau.

taille du tableau = 100

[c] = 99 , [h] = 104 , [a] = 97 , [T] = 116

( 99 + 104 + 97 + 116) % 100 = 16

Et voila nous pouvons enregistrer felix à l'index 16 de notre tableau.
Vous l'avez compris, rien de bien compliqué.

### En principe

Comme vous l'avez vu précédemment, le principe est simple, mais en pratique c'est un petit peu plus compliqué.
Tout d'abord, ce système comporte quelques "imprévus": les collisions. Il se peut que deux clefs totalement différentes
aient, grâce à un algorithme, le même index. Pour résoudre ceci, j'ai opté pour l'utilisation d'une liste sur chaque index.
Plus le nombre de collisions est grand, plus l'efficacité/rapidité d'un hash est réduit car s'il y a 2 valeurs à un index, vous devrez
comparer chacune des valeurs de la même façon que si vous travaillez avec une simple liste.
Selon l'algorithme choisi, vous pourrez diminuer le nombre de collisions.
Autre point important, plus le tableau est grand et plus le nombre de collisions diminue (ceci n'est pas vrai avec l'algorithme vu précédemment qui, peu importe la taille du tableau, donnera sensiblement le même index).

Conclusion, le choix de l'algorithme est important pour limiter le nombre de collisions et la taille du tableau doit être un bon compromis entre utilisation de la mémoire et rapidité.

## Ma solution

Je vous propose, à l'aide des fonctions ci-dessous une totale abstraction de ces problématiques, mis à part la taille du tableau
qui devra être choisie avec soin selon vos besoins (il est évident que partir sur un tableau au moins aussi grand que le nombre d'insertions est vivement conseillé).

### t_hash

Un hash est une structure contenant le nom du hash, le nombre d'éléments, sa taille et un tableau de t_elem.

```
typedef struct s_hash		t_hash;
struct				s_hash
{
	char			*name;
	int			size;
	int			nb_elem;
	t_elem			**hash_tab;
};
```

### t_elem

Un élément est composé d'une clef qui servira lors de la recherche de cet élément et d'une valeur.
Chaque élément peut être suivi par d'autres éléments qui auront été placés sur le même index du tableau **hash_tab.

```
typedef struct s_elem		t_elem;
struct						s_elem
{
	char					*key;
	char					*value;
	t_elem					*next;
};
```


### Créer un hash
Ce code permet de générer un hash de 500 entrées. Mais comme dit plus haut, rien ne vous empêchera de stocker 600
valeurs si vous le souhaitez. J'insiste seulement sur le fait que, si vous insérez plus d'éléments qu'il ny a d'entrées, les performances seront excessivement réduites.

#### Prototype
```
t_hash						*create_hash(char *name, int size);
```
#### Usage
```
t_hash mon_hash = create_hash("binaire", 500);
```
### Ajouter une clef et une valeur (un elem)
Rien de plus simple que d'ajouter une clef et une valeur.
Les chaînes de caractères key et str seront des copies grâce à strdup.
L'elem créé est renvoyé.
#### Prototype
```
t_elem					*h_add_elem(t_hash *hash, char *key, char *value);
```
#### Usage
```
char *key = "chat";
char *value = "Felix";

h_add_elem(mon_hash, key, value);
```
## Supprimer un elem
Permet de supprimer une paire clef/valeur grâce à une clef.
Renvoie 0 si aucune paire n'a été supprimée et 1 si oui.
#### Prototype
```
int					h_delete_elem(t_hash *hash, char *key);
```
#### Usage
```
if (!h_delete_elem(mo_hash, "chien")
	printf("Mince ya que des chat ici");
```

## Récuperer un élément du hash
Renvoie un elem ou NULL grâce à une clef.

#### Prototype
```
t_elem					*h_get_elem_by_key(t_hash *hash, char *key);
```
#### Usage
```
	t_elem *mon_chat;
	
	if ((mon_chat = h_get_elem_by_key(mo_hash, "chat")))
		printf("Youpi j'ai retrouver mon chat");
```

## Récupérer la copie d'une valeur
Renvoie une copie(strdup) d'une valeur touvée grâce à une clef.
Ou null si aucun n'elem n'a été trouvé.

#### Prototype
```
char					*h_get_value_by_key(t_hash *hash, char *key)
```
#### Usage
```
char *mon_chat;

mon_chat = h_get_value_by_key(mon_hash, "chat");

```

## Modifier ou créer une paire clef/valeur
Cette fontion modifie un élément s'il existe grâce à sa clef ou le cré si aucun élément n'est touvé.
Renvoie l'elem créé.
#### Prototype
```
t_elem					*h_set_or_create_elem(t_hash *hash, char *key, char *value);
```
#### Usage
```
t_elem chient = h_set_or_create_elem(mon_hash, "chien", "choubi"); 
```
## Transformer une chaîne de caractères en une paire clef/valeur
Fonction très utile qui permet de créer un elem à partir d'une simple chaîne et d'un séparateur.

exemple: 

str = "PATH=$PATH:/usr/bin"
c = '='
clef -> "PATH"
value -> "$PATH:/usr/bin"

#### Prototype
```
void						h_split_store_elem(t_hash *hash, char *str, char c);
```
#### Usage
```
char *str = "PATH=$PATH:/usr/bin";

h_split_store_elem(mon_hash, str, 'c');
```
## Afficher le hash
Affiche le hash en fonction des paramètres désirés.

#### Prototype
```
void						h_print(t_hash *hash, int opts);
```
#### Usage
```
h_print(mon_hash, VAL_OK|NUM_OK|LEN_OK);
```
## Création d'un tableau à partir d'un hash
Tout est dans le titre, simple copie d'un hash sous la forme d'un tableau.

#### Prototype
```
char						**hash_to_tab(t_hash *hash);
```
#### Usage
```
char **tab;

tab = has_to_tab(mon_hash);
```
## Suppression totale d'un hash ou de ses elem
Cette fonction prend un paramètre full, si ce paramètre vaut 1, la suppression sera totale et le hash vaudra null.
Sinon si full vaut 0 le hash sera simplement réinitialisé et vous pourrez continuer de vous en servir comme avant.
#### Prototype
```
void						h_free(t_hash **hash, int full);
```
#### Usage
```
h_free(mon_hash, 1);
```
