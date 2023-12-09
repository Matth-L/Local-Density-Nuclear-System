\mainpage

##Introduction
Ce projet consiste à calculer la densité locale d'un système nucléaire. Cette densité représente la probabilité de trouver de la matière nucléaire dans une position donnée.

##Contexte physique
###Forme de la densité

La densité locale nucléaire \f$\rho(r)\f$ peut être obtenue à partir de la densité matricielle (complexe) fournie {\f$\rho_{ab}\f$} en utilisant un ensemble de functions d'une base {\f$\psi_i(r)\f$}:

\f$\rho(r) \equiv \sum_{a}^{} \sum_{b}^{} \rho_{ab}\psi_a(r)\psi_b^{*}(r)\f$

avec:

- les entiers positifs \f$a,b\f$, appelés les indices de la base

- chaque fonction de base est définie par un unique ensemble d'entiers positifs (\f$m,n,n_z\f$), appelés les chiffres quantiques

On peut donc écrire:
\f$\psi_a = \psi_{m_a,n_a,n_{za}}\f$

Finalement, l'expression de \f$\rho(r)\f$ peut aussi être exprimée avec les chiffres quantiques
L'ensemble des fonctions de la base devrait être infini, mais dans notre cas, on utilisera une troncation de la base.

###Fonctions de la base
Elles sont définies avec les coordonnées cylindriques \f$r \equiv (r_{\bot},\theta,z)\f$:

\f$\psi_{m,n,n_z}(r_{\bot},\theta,z) \equiv Z(z,n_z).R(r_{\bot},m,n).e^{im\theta}\f$

avec:

- \f$Z(z,n_z) \equiv \frac{1}{\sqrt{b_z}}\frac{1}{\sqrt{2^{n_z}\sqrt{\pi}n_z!}}e^{-\frac{z^2}{2b_z^2}}H_{n_z}(\frac{z}{b_z})\f$

- \f$R(r_{\bot},m,n) \equiv \frac{1}{b_{\bot}\sqrt{\pi}}\sqrt{\frac{n!}{(n+|m|)!}}e^{-\frac{r_{\bot}^2}{2b_{\bot}^2}}(\frac{r_{\bot}}{b_{\bot}})^{|m|}L_n^{|m|}(\frac{r_{\bot}^2}{b_{\bot}^2})\f$

avec
- \f$b_{\bot},b_z\f$ les paramètres de déformation de la base
- \f$H_k(\zeta)\f$ les polynômes d'Hermite
- \f$L_k^m(\eta)\f$ les polynômes de Laguerre généralisé

###Polynômes d'Hermite et de Laguerre

Ici, nous utilisons la définition par réccurence de ces polynômes:

Hermite:

\f$
\begin{aligned}
H_{0}(\zeta) &= 1 \\

H_{1}(\zeta) &= 2z \\

\forall n \in \mathbb{N}^{+}, n > 1,H_{n+1}(\zeta) &= 2\zeta H_{n}(\zeta) - 2nH_{n-1}(\zeta)
\end{aligned}
\f$

Laguerre généralisé:

\f$
\begin{aligned}
L_{0}^m(\eta) &= 1 \\

L_{1}^m(\eta) &= 1 + m - \eta \\

\forall (m, n) \in \mathbb{N}^{+2}, n > 1,L_n^m(\eta) &= (2+\frac{m-1-\eta}{n})L_{n-1}^m(\eta) - (1+\frac{m-1}{n})L_{n-2}^m(\eta)
\end{aligned}
\f$

###Troncation de la base

Le principe est de tronquer la base \f$(m,n,n_z)\f$. Pour faire cela, il nous faut:

- \f$\nu(i) \equiv (N+2).Q^{\frac{2}{3}} + \frac{1}{2} - i.Q\f$
- \f$m^{max} \equiv sup(i:\nu{i} \ge 1)\f$

avec \f$ N \in \mathbb{N}^{+},Q \in \mathbb{R}^{+}\f$ les paramètres de troncation de la base

Les valeurs possibles pour chacun des chiffres quantiques sont définis de la façon suivante:

\f$0 \le m < mMax \equiv m^{max}\f$

\f$0 \le n < nMax[m] \equiv \frac{1}{2}(m^{max}-m-1)+1\f$

\f$0 \le n_z < n_{z}Max[m,n] \equiv \nu(m+m^{max}+1)\f$