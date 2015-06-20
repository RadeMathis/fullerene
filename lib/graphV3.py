import os, platform, subprocess, random, glob, sys
#from random import randrange

# Attention, eviter que les deux noms globaux qui suivent
# aient meme prefixe que les noms "publics"
# proposes par Idle (completion de nom);
# on pourrait evidemment ajouter un _ en tete

plateforme = platform.system ()

pathGraphviz = ''

if plateforme == 'Windows':
    l = glob.glob('C:/Program Files*/Graphviz*/bin/dot.exe')
    if l == []:
        print("Graphviz non trouve, veuillez l'installer")
        sys.exit(1)
    path = l[0]
    pathGraphviz = path[0:-7]
if plateforme == 'Darwin': # pour mac
    pathGraphviz = '/usr/local/bin/'


################ PRIMITIVES GENERIQUES SUR LES LISTES   ##############

def melange (u):
    v = u[:] # v est une copie de u, Python c'est fun
    random.shuffle (v)
    return v

def elementAleatoireListe(u):
  # u est une liste
  # La fonction renvoie un element pris au hasard de la liste u si 
  # elle est non-vide. Si u est vide, la fonction renvoie une 
  # erreur (exception IndexError)
    return random.choice(u)



# Changelog JB
#   Ete 2009
#     Grand nettoyage et adaptation a Python 3
#   Septembre 2009: variable globale plateforme
#     evite deux appels systeme a chaque dessin
#     simplification des fonctions Graphviz et dessinerGraphe
#     (suggestions Jean-Claude Ville)
#   Octobre 2009: utilisation de la mise en forme de chaines
#     (format % valeurs) pour simplifier les representations de classes
#     (methodes __repr__) et la fonction 'dotify'
#   Janvier 2010: fonction 'voisinPar' -> 'sommetVoisin'

################ PRIMITIVES GRAPHE   #################################

def nomGraphe(G):
    verif_type_graphe(G)
    return G.label

def listeSommets(G):
    verif_type_graphe(G)
    return G.nodes

def nbSommets(G):
    return len(listeSommets(G))

def sommetNom(G, etiquette):
    for s in listeSommets(G):
        if s.label == etiquette:
            return s
    return None

def sommetNumero(G, i):
    return listeSommets(G)[i]

################# PRIMITIVES SOMMET   ###################################

def nomSommet(s):
    verif_type_sommet(s)
    return s.label

def marquerSommet(s):
    verif_type_sommet(s)
    s.mark = True

def demarquerSommet(s):
    verif_type_sommet(s)
    s.mark = False

def estMarqueSommet(s):
    verif_type_sommet(s)
    return s.mark

def colorierSommet(s, c):
    verif_type_sommet(s)
    verif_type_chaine(c)
    s.color = c

def couleurSommet(s):
    verif_type_sommet(s)
    return s.color

##Dans cette version on ne colorie pas les aretes
##colorier = colorierSommet
##couleur = couleurSommet
    
# Ici les choses serieuses
def listeAretesIncidentes(s):
    verif_type_sommet(s)
    return s.edges

def areteNumero(s, i):
    return listeAretesIncidentes(s)[i]

def degre(s) :
    return len(listeAretesIncidentes(s)) 

def listeVoisins(s):
    inc = listeAretesIncidentes(s)
    v = []
    for a in inc:
        if a.start == s:
            v.append (a.end)
        elif a.end == s:
            v.append (a.start)
    return v

def voisinNumero(s, i):
    return listeVoisins(s)[i]

def sommetVoisin(s, a):
    verif_type_sommet(s)
    verif_type_arete(a)
    if a.start == s:
        return a.end
    if a.end == s:
        return a.start
    return None

################ PRIMITIVES arete ########################

def nomArete(a):
    verif_type_arete(a)
    return a.label

def marquerArete(a):
    verif_type_arete(a)
    a.mark = True

def demarquerArete(a):
    verif_type_arete(a)
    a.mark = False

def estMarqueeArete(a):
    verif_type_arete(a)
    return a.mark

def numeroterArete(a, n):
    verif_type_arete(a)
    a.label = str(n)

################ Classes ########################

class c_graph:
    def __init__(self, label = '', drawopts = ''):
        self.nodes = []
        self.label = label
        self.drawopts = drawopts    # pour Graphviz
    def __repr__(self):
        return "<graphe: '%s'>" % self.label

class c_node:
    def __init__(self, label = '', color = 'white', mark = False, drawopts = ''):
        self.label = label
        self.color = color
        self.mark = mark
        self.edges = []
        self.drawopts = drawopts    # pour Graphviz
    def __repr__(self):
        c = "'" + self.color + "'"
        return "<sommet: '%s', %s, %s>" % (self.label, c, self.mark)

class c_edge:
    def __init__(self, label = '', start = None, end = None, mark = False, drawopts = ''):
        self.label = label
        self.start = start
        self.end = end
        self.mark = mark
        self.drawopts = drawopts    # pour Graphviz
    def __repr__(self):
        return "<arete: '%s' %s--%s>" % (self.label, self.start.label, self.end.label)

################ Verifications de types ########################

def verif_type_graphe(G):
    if G.__class__.__name__ != 'c_graph':
        raise ErreurParametre(G, "un graphe")
    
def verif_type_sommet(s):
    if s.__class__.__name__ != 'c_node':
        raise ErreurParametre(s, "un sommet")

def verif_type_arete(a):
    if a.__class__.__name__ != 'c_edge':
        raise ErreurParametre(a, "une arete")

def verif_type_chaine(s):
    if type(s) != str:
        raise ErreurParametre(s, "une chaine de caracteres")

class ErreurParametre (Exception):
    def __init__(self, arg, param):
        self.arg = arg
        self.param = param
    def __str__(self):
        # affichage discutable
        if type (self.arg) == str:
            strArg = "'" + self.arg + "'"
        else:
            strArg = str (self.arg)
        return strArg + " n'est pas " + self.param

############### Construction de graphes  #####################
    
def _add_edge (G, label, i, j):
    a = c_edge(label, G.nodes[i], G.nodes[j])
    G.nodes[i].edges.append(a)
    G.nodes[j].edges.append(a)
    return a

# retourne le numero du sommet
def _find_add_node (G, nom):
    i = 0
    for s in G.nodes:
        if s.label == nom:
            return i
        i = i + 1
    G.nodes.append (c_node (nom))
    return i

# Un chemin p est une liste de noms de sommets ['A', 'B', 'C', ...]
# Le parametre booleen 'chemins' indique si les aretes sont:
#   A-B, B-C, etc. (chemin classique)
#   A-B, A-C, etc. (etoile: le sommet initial est suivi de ses voisins)
# B, C, etc. peuvent aussi etre des couples [nom de sommet, nom d'arete]
# lorsqu'on veut etiqueter explicitement les aretes
# (etiquetees par defaut 'e0', 'e1', etc. dans l'ordre de leur creation)

# Attention: l'etiquette d'un graphe (label) sert aussi de nom de fichier
# pour les dessins, eviter les blancs, etc

def construireGraphe (paths, label, chemins = True):
    G = c_graph(label)
    
    # Numeroter les aretes a partir de 0 ou 1 en l'absence
    # d'etiquette explicite?
    # On choisit 1 car les dessins du poly adoptent cette convention
    # mais ce choix est incoherent avec celui pour les sommets:
    # la fonction sommetNumero impose que les sommets des graphes
    # generiques (grilles, etc) soient etiquetes 's0', 's1', etc.
    # Voir bibV3
    
    nba = 1
    for p in paths:
        labelsource = p[0]
        i = _find_add_node (G, labelsource);
        
        # ne pas utiliser 'for a in p' car il faut maintenant ignorer p[0]  
        for k in range (1, len(p)):
            a = p[k]
            edge_with_label = type(a) == type([])
            if edge_with_label:
                labeldestination = a[0]
                labeledge = a[1]
            else:
                labeldestination = a
                labeledge = 'e' + str(nba)
                nba = nba + 1
            j = _find_add_node(G, labeldestination)
            _add_edge(G, labeledge, i, j)
            if chemins:
                i = j
    return G

############### Dessin du graphe  #####################

# fonction necessaire a cause par exemple des 'Pays Bas' (blanc dans label)
def _proteger (label):
    return '"' + label + '"'

# La fonction 'dotify' transforme le graphe en un fichier texte
# qui servira de source (suffixe .dot) pour les programmes de Graphviz.
# Cette fonction ne depend pas du systeme d'exploitation.

def dotify (G, etiquettesAretes = True, colormark = 'Black', suffixe = 'dot'):

    # graphe non oriente, il faut eviter de traiter chaque arete deux fois
    for s in G.nodes:
        for a in s.edges:
            a.ecrite = False
            
    if G.label == '':
        nom_graphe = 'G'
    else:
        nom_graphe = G.label

    graph_dot = 'tmp/' + nom_graphe + '.' + suffixe
        
    try:
        f = open (graph_dot, 'w')
    except IOError:
        os.mkdir ('tmp')
        f = open (graph_dot, 'w')
        
    f.write ('graph "' + nom_graphe + '" {\n' + G.drawopts + '\n')

    for s in G.nodes:
        d = len (s.edges)
        snom = _proteger (s.label)
        for a in s.edges:
            if not a.ecrite:
                a.ecrite = True
                if a.start == s:
                    t = a.end
                else:
                    t = a.start
                f.write ('  ' + snom + ' -- ' + _proteger (t.label))
                if etiquettesAretes:
                    f.write (' [label = ' + _proteger (a.label) + ']')
                if a.mark:
                    f.write (' [style = bold, color = orange]')
                # Semicolons aid readability but are not required (dotguide.pdf)
                f.write (a.drawopts + ';\n')
        bord = 'black'
        if s.mark:
            entoure = 2
            bord = colormark
        else:
            entoure = 1
        if s.color:
            if s.color == "black":
                fontcolor = "white"
            else:
                fontcolor = "black"
            f.write ('  %s [style = filled, peripheries = %s, fillcolor = %s, fontcolor = %s, color = %s] %s;\n' %
                     (snom, entoure, s.color, fontcolor, bord, s.drawopts))
        elif s.mark:
##            f.write ('  ' + snom + ' [peripheries = 2, color = ' + bord + ']' +
##                     s.drawopts + ';\n');
            f.write ('  %s [peripheries = 2, color = %s] %s;\n' %
                     (snom, bord, s.drawopts))
        elif d == 0 or s.drawopts:
            f.write ('  ' + snom + s.drawopts + ';\n')
            
    f.write ('}\n')
    f.close ()
    return graph_dot

# La fonction 'Graphviz' lance l'execution d'un programme
# de la distribution Graphviz (dot, neato, twopi, circo, fdp)
# pour transformer un fichier texte source de nom 'racine.suffixe'
# en une image de nom 'racine.format' (peut-etre un fichier PostScript)

def Graphviz (source, algo = 'dot', format = 'svg', suffixe = 'dot'):
    image = source.replace ('.' + suffixe, '.' + format)
    algo = pathGraphviz + algo
    if plateforme == 'Windows':
        algo = algo + '.exe'
    subprocess.call ([algo, '-T' + format, source, '-o', image])
    return image

# Enchaine dotify et Graphviz avec des arguments standard adaptes au systeme
# et lance le programme ad hoc pour afficher l'image

def dessinerGraphe (G, etiquettesAretes = False, algo = 'dot', colormark = 'Black'):
    verif_type_graphe (G)
    sys = platform.system ()
    if plateforme == 'Windows':
        # eviter toute embrouille avec les modeles de document de MS Word
        graph_dot = dotify (G, etiquettesAretes, colormark, 'txt')
        image = Graphviz (graph_dot, algo, suffixe = 'txt')
        image = image.replace ('/', '\\')
        os.startfile (image)
        return

    graph_dot = dotify (G, etiquettesAretes, colormark)
    image = Graphviz (graph_dot, algo)
    if plateforme == 'Linux':
        #subprocess.call (['firefox', image])
        subprocess.Popen (['firefox ' + image + ' &'], shell=True)
    elif plateforme == 'Darwin':
        subprocess.call (['open', image])
    else:
        print("Systeme " + plateforme + " imprevu, abandon du dessin")
        
dessiner = dessinerGraphe

# Cela pourrait être mieux écrit avec des règles standards de lexing/parsing, mais cela évite des dépendances

def _charclass (c):
    if c >= 'a' and c <= 'z' or \
           c >= 'A' and c <= 'Z' or \
           c >= '1' and c <= '9' or \
           c == '0' or  c == '_' or c == '.':
        return 'a'
    if c == '-' or c == '>':
        return '-'
    return c

# Lexing. On commence à regarder à la position i
# Retourne le mot et la position à laquelle on est arrivé
def _mot (s, debut):
    while debut < len(s) and (s[debut] == ' ' or s[debut] == '\t' or s[debut] == '\n' or s[debut] == '\r'):
        debut+=1

    if debut >= len(s):
        return "",debut

    if s[debut:debut+2] == '/*':
        fin = debut + 2
        while s[fin:fin+2] != '*/':
            fin+=1
        return _mot(s, fin+2)

    fin = debut
    if s[debut] == '"':
        fin+=1
        echappe = False
        while fin < len(s):
            if echappe:
                echappe = False
            else:
                if s[fin] == '"':
                    #print(s[debut:fin+1],fin+1)
                    return s[debut:fin+1],fin+1
                if s[fin] == '\\':
                    echappe = True
            fin+=1
        raise SyntaxError("Fichier incorrect: \" not terminé à la fin du fichier")

    charclass = _charclass(s[fin])
    while fin < len(s) and (s[fin] != ' ' and s[fin] != '\t' and s[fin] != '\n' and s[fin] != '\r'):
        if s[fin] == '#':
            # Commentaire, ignore jusqu'à la fin de ligne
            fin2 = fin
            while fin2 < len(s) and (s[fin2] != '\n' and s[fin2] != '\r'):
                fin2+=1
            if debut == fin:
                # Pas de mot avant le commentaire, on recommence à lire à la ligne suivante
                return _mot(s, fin2)
            return s[debut:fin],fin2

        if _charclass(s[fin]) != charclass:
            # On change de class de caractère, cela découpe le mot
            #print(s[debut:fin],fin)
            return s[debut:fin],fin

        if s[fin] == '"':
            raise SyntaxError("Fichier incorrect: \" au milieu d'un mot à "+str(debut))
        fin+=1
    #print(s[debut:fin],fin+1)
    return s[debut:fin],fin+1

# Parsing

# Lit le contenu d'attributs. Le [ initial a déjà été consommé. On commence à regarder à la position i
# Retourne un dictionnaire des attributs et la position à laquelle on est arrivé
def _attributs(s,i):
    nom,i = _mot(s,i)
    attributs = {}
    while nom != ']':
        if nom == "":
            raise SyntaxError("Fichier incorrect: pas de crochet fermant à "+str(i))
        if nom == ",":
            nom,i = _mot(s,i)
        egal,i = _mot(s,i)
        if egal != '=':
            raise SyntaxError("Fichier incorrect: trouvé "+egal+" au lieu d'un '=' à "+str(i))
        val,i = _mot(s,i)
        #print("attribut "+nom+" défini à "+val+" .")
        attributs[nom] = val
        nom,i = _mot(s,i)
    return attributs,i

# Lit une définion de graphe, en commançant par son nom à la position i
# Retourne une liste de chemins et la nouvelle position
def _litgrapheDOT(s,i):
    chemins = []
    couleurs = []
    nom,i = _mot(s,i)
    if nom[0] == '"':
        nom = nom[1:-1]
    accolade,i = _mot(s,i)
    if accolade != "{":
        raise SyntaxError("Fichier incorrect: trouvé "+accolade+" au lieu d'une accolade ouvrante à "+str(i))

    mot,i = _mot(s,i)
    while mot != "}":
        #print("starting new read with "+mot+" "+str(i))
        if mot == "":
            raise SyntaxError("Fichier incorrect: pas d'accolade fermante terminale à la fin du fichier")

        if mot == "graph" or mot == "node" or mot == "edge":
            # attributs par défaut, on ignore
            crochet,j = _mot(s,i)
            if crochet != '[':
                raise SyntaxError("Fichier incorrect: trouvé "+crochet+" au lieu d'un crochet ouvrant à "+str(i)+' '+str(j))
            i = j
            attr,i = _attributs(s,i)
            if mot == "node" and "fillcolor" in attr:
                couleurDefautSommet = attr["fillcolor"]
            mot,i = _mot(s,i)

        elif mot == "subgraph":
            # récursion!
            # idéalement il faudrait séparer les espaces de noms de sommets
            _,chemins_sousgraphe,couleurs_sougraphe,i = _litgrapheDOT(s,i)
            couleurs = chemins_sousgraphe + couleurs
            chemins = chemins_sousgraphe + chemins
            mot,i = _mot(s,i)

        else:
            # Nom d'un sommet
            if mot[0] == '"':
                mot = mot[1:-1]
            mot2,i = _mot(s,i)
            chemins += [[mot]]
            if mot2 == '[':
                # attributs d'un nœud
                attr,i = _attributs(s,i)
                if "fillcolor" in attr:
                    couleurSommet = attr["fillcolor"]
                    couleurs += [(mot, couleurSommet)]
                mot,i = _mot(s,i)
            elif mot2 == '--' or mot2 == '->':
                # Un chemin
                chemin = [mot]
                mot = mot2
                while mot == '--' or mot == '->':
                    mot,i = _mot(s,i)
                    if mot[0] == '"':
                        mot = mot[1:-1]
                    chemin = [mot] + chemin
                    mot,i = _mot(s,i)
                chemins += [chemin]
                if mot == '[':
                    # attributs d'un chemin, ignore
                    attr,i = _attributs(s,i)
                    mot,i = _mot(s,i)
            elif mot2 == '=':
                # attribut par défaut
                mot3,i = _mot(s,i)
                if mot == 'fillcolor':
                    couleurDefautSommet = mot3
                mot,i = _mot(s,i)
            elif mot2 == ';':
                # Rien d'intéressant, en fait
                mot = mot2
            else:
                raise SyntaxError("Fichier non supporté: trouvé "+mot2+" à "+str(i))
        while mot == ';':
            mot,i = _mot(s,i)
    return nom,chemins,couleurs,i

def _litgrapheGML(s,i):
    chemins = []
    couleurs = []
    noms = {}
    graph,i = _mot(s,i)
    if graph != "graph":
        raise SyntaxError('Attendu "graph", trouvé '+graph+' à la place')
    mot,i = _mot(s,i)
    if mot != '[':
        raise SyntaxError('Attendu "[", trouvé '+mot+' à la place')
    mot,i = _mot(s,i)
    while mot != ']':
        if mot == "directed":
            oriente,i = _mot(s,i)
            mot,i = _mot(s,i)
        elif mot == "node":
            # un sommet
            mot,i = _mot(s,i)
            if mot != '[':
                raise SyntaxError('Attendu "[", trouvé '+mot+' à la place')
            mot,i = _mot(s,i)
            ID = -1
            nom = ""
            while mot != ']':
                if mot == 'id':
                    ID,i = _mot(s,i)
                    mot,i = _mot(s,i)
                elif mot == 'label':
                    nom,i = _mot(s,i)
                    if nom[0] == '"':
                        nom = nom[1:-1]
                    mot,i = _mot(s,i)
                elif mot == 'value':
                    # ignore
                    value,i = _mot(s,i)
                    mot,i = _mot(s,i)
                else:
                    raise SyntaxError('mot-clé de sommet '+mot+' non supporté à '+str(i))
            if nom == "":
                nom = str(ID)
            noms[ID] = nom
            chemins += [[nom]]
            mot,i = _mot(s,i)
        elif mot == "edge":
            # une arête
            mot,i = _mot(s,i)
            if mot != '[':
                raise SyntaxError('Attendu "[", trouvé '+mot+' à la place')
            mot,i = _mot(s,i)
            src = ''
            dst = ''
            while mot != ']':
                if mot == 'source':
                    src,i = _mot(s,i)
                    mot,i = _mot(s,i)
                elif mot == 'target':
                    dst,i = _mot(s,i)
                    mot,i = _mot(s,i)
                elif mot == 'value':
                    value,i = _mot(s,i)
                    mot,i = _mot(s,i)
                else:
                    raise SyntaxError('mot-clé de sommet '+mot+' non supporté à '+str(i))
            if src == '':
                raise SyntaxError("source de l'arête manquante")
            if dst == '':
                raise SyntaxError("destination de l'arête manquante")
            chemins += [[noms[src],noms[dst]]]
            mot,i = _mot(s,i)
        else:
            raise SyntaxError('mot-clé '+mot+' non supporté à '+str(i))

    return "graphe",chemins,couleurs,i

def _litgraphePAJ(s,i):
    chemins = []
    couleurs = []
    noms = {}
    nbvert,i = _mot(s,i)

    mot,i = _mot(s,i)
    while mot != "*Edges":
        # un sommet
        ID = mot
        nom,i = _mot(s,i)
        if nom[0] == '"':
            nom = nom[1:-1]
        noms[ID] = nom
        chemins += [[nom]]

    mot,i = _mot(s,i)
    while mot != "*Edges":
        # une arête
        src = mot
        dst,i = _mot(s,i)
        chemins += [[noms[src],noms[dst]]]

    return "graphe",chemins,couleurs,i

# Parsing
def ouvrirGraphe(nom):
    f = open(nom)
    s = f.read()
    i = 0

    couleurDefautSommet = "white"

    graph,i = _mot(s,i)
    if graph == "Creator":
        # .gml format
        creator,i = _mot(s,i)
        nom,chemins,couleurs,i = _litgrapheGML(s,i)
    elif graph == "*Vertices":
        # .paj format
        nom,chemins,couleurs,i = _litgraphePAJ(s,i)
    else:
        if graph == "strict":
            graph,i = _mot(s,i)
        if graph == "digraph":
            oriente = True
        elif graph == "graph":
            oriente = False
        else:
            raise SyntaxError("Fichier .dot de type "+graph+" non supporté")

        nom,chemins,couleurs,i = _litgrapheDOT(s,i)
    g = construireGraphe(chemins, nom)
    for (s,c) in couleurs:
        colorierSommet(sommetNom(g,s),c)
    return g

print("graphV3.py")
