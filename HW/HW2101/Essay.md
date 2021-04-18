## Identities of Regular Expression

$A\varnothing = \varnothing A = \varnothing$
$A\{\varepsilon\} = \{\varepsilon\}A = A$
$(AB)C = A(BC)$
$(A \subseteq B) \wedge (C \subseteq D) \Rightarrow AC \subseteq BD$
$A(B \cup C) = AB \cup AC$
$(B \cup C)A = BA \cup CA$
$A(B \cap C) \subseteq AB \cap AC$
$(B \cap C)A \subseteq BA \cap CA$
$A^* = A^+ \cup \{\varepsilon\}$
$A^n \subseteq A^*, n ≥ 0$
$A^n \subseteq A^+, n ≥ 1$
$A \subseteq AB^*$
$A \subseteq B^*A $
$A \subseteq B \Rightarrow A^* \subseteq B^*$
$A \subseteq B \Rightarrow A^+ \subseteq B^+$
$AA^* = A^*A = A^+$
$\{\varepsilon\} \in A$ iff $A^+ = A^*$
$(A^*)^* = A^*A^* = A^*$
$(A^*)^+ = (A^+)^* = A^*$
$A^*A^+ = A^+A^* = A^*$
$(A^*B^*)^* = (A \cup B)^* = (A^* \cup B^*)^*$
$(C = AC \cup B) \Rightarrow (C = A^*B)$

## Nomor 1

Untuk setiap $L_1, L_2,$ dan $L_3$, $(L_1^*(L_2 \cup L_3)^*)^* = ((L_1 \cup L_2)^*L_3^*)^*$ .

**Ya**, perhatikan bahwa $(A^*B^*)^* = (A \cup B)^*$

To show that $L(R_2)\subseteq L(R_1)$ you should note that $L(A)\subseteq L(A^*)\subseteq L(A^* B^*)$, analogously $L(B)\subseteq L(A^* B^*)$, so $L(A+B)\subseteq L(A^* B^*)$ ah hence $L((A+B)^*)\subseteq L((A^* B^*)^*)$.
For the converse, note that $L(A)\subseteq L(A+B)\subseteq L((A+B)^*)$ and (being the latter concatenation-closed) $L(A^*)\subseteq L(((A+B)^*)^*)=L((A+B)^*)$ analogously $L(B^*)\subseteq L((A+B)^*)$, so, again for concatenation closedness $L(A^*B^*)\subseteq L((A+B)^*)$ and you finally have (for the same reason) $L((A^*B^*)^*)\subseteq L((A+B)^*)$.
$$
\begin{align}
(L_1^*(L_2 \cup L_3)^*)^* &= ((L_1 \cup L_2)^*L_3^*)^* \\
(L_1 \cup(L_2 \cup L_3))^* &= ((L_1 \cup L_2) \cup L_3)^* \\
(L_1 \cup L_2 \cup L_3)^* &= (L_1 \cup L_2 \cup L_3)^*
\end{align}
$$

## Nomor 2

Untuk setiap $L_1$ dan $L_2$, berlaku $L_1  = L_2 \iff L_1^* = L_2^*$.

**Tidak**, kasus sanggahannya ialah saat $L_1 = \{a\}; L_2 = \{a,aa\};$ Jelas bahwa $a^2 = aa$, sehingga $L_1^* = L_2^*$, namun $L_1 \ne L_2$.

## Nomor 3

Untuk setiap $L_1$ dan $L_2$, benar $(L_1 \cap L_2)^*(L_1 \cup L_2)^* = (L_1 \cup L_2)^*L_2^*$

**Ya**, Perhatikan bahwa ${B \subseteq A} \implies A^*B^* = A^*$.
$$
\textbf{Proof}\\
\{\varepsilon\} \in B^* \implies A^* \subseteq A^*B^* \\
B \subseteq A \implies B^* \subseteq A^* \implies   A^*B^* \subseteq A^*A^* = A^*\\
$$

$$
\textbf{Implies}\\
A^* \subseteq A^*B^* \wedge A^*B^* \subseteq A^* \implies A^*B^* = A^*
$$

Dengan bukti yang serupa, didapatkan juga bahwa ${A \subseteq B} \implies B^*A^* = A^*$.

Perhatikan bahwa berlaku pula ${L_1 \cap L_2} \subseteq {L_1 \cup L_2}$ dan $L_2 \subseteq L_1 \cup L_2$, dari lemma di atas, dapat disimpulkan  bahwa $(L_1 \cap L_2)^*(L_1 \cup L_2)^* = (L_1 \cup L_2)^*L_2^* = (L_1 \cup L_2)^*$.

## Nomor 4

$L = \{w \in \{a, b\}^*: \#_a(w) \text{ genap dan } \#_b(w) \text{ ganjil}\}$ bersifat tertutup (closed) terhadap operasi triplikasi $www$ ($L$ tertutup terhadap triplikasi: jika $w$ adalah string dari $L$ maka juga $www$ adalah juga di dalam $L$).

**Ya**, misalkan sebuah string $w \in L$, dan misalkan operasi triplikasi $F$ pada string $w$ sebagai $F(w)$. Untuk sembarang string $w$, berlaku $\#_a(w) = 2i; \#_b(w) = 2j + 1;$ untuk suatu bilangan bulat non negatif $i$ dan $j$. Asumsikan $F(w)$ akan menghasilkan string $x$. Maka, $\#_a(x) = 3\cdot\#_a(w) = 6i; \#_b(x) = 3 \cdot \#_b(w) = 3(2j + 1) = 6j + 3 = 2(3j + 1) + 1;$ Selanjutnya, perhatikan bahwa $\#_a(x)$ dan $\#_b(x)$ dapat dinyatakan dalam $2c$ dan $2d + 1$ secara berturut-turut untuk bilangan bulat non negatif $c$ dan $d$. Dapat disimpulkan bahwa $\#_a(x)$ genap dan $\#_b(x)$ ganjil. Sehingga, string $x$ terdapat di $L$. Maka, terbukti bahwa $L$ bersifat tertutup (*closed*) terhadap operasi triplikasi $F(w) = www$.