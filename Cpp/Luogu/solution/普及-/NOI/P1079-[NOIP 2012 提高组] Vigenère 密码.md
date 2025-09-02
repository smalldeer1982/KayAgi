# [NOIP 2012 提高组] Vigenère 密码

## 题目描述

16 世纪法国外交家 Blaise de Vigenère 设计了一种多表密码加密算法 Vigenère 密码。Vigenère 密码的加密解密算法简单易用，且破译难度比较高，曾在美国南北战争中为南军所广泛使用。

 
在密码学中，我们称需要加密的信息为明文，用 $M$ 表示；称加密后的信息为密文，用 $C$ 表示；而密钥是一种参数，是将明文转换为密文或将密文转换为明文的算法中输入的数据，记为 $k$。在 Vigenère 密码中，密钥 $k$ 是一个字母串，$k=k_1,k_2,…,k_n$。当明文 $M=m_1,m_2,…,m_n$ 时，得到的密文 $C=c_1,c_2,…,c_n$，其中 $c_i$=$m_i \operatorname{\circledR} k_i$，运算 $\circledR$ 的规则如下表所示：

$$\begin{array}{c|cccccccccccccccccccccccccc}
\circledR &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt}  \\\hline
\tt A &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt}  \\
\tt B &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt}  \\
\tt C &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt}  \\
\tt D &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt}  \\
\tt E &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt}  \\
\tt F &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt}  \\
\tt G &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt}  \\
\tt H &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt}  \\
\tt I &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt}  \\
\tt J &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt}  \\
\tt K &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt}  \\
\tt L &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt}  \\
\tt M &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt}  \\
\tt N &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt}  \\
\tt O &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt}  \\
\tt P &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt}  \\
\tt Q &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt}  \\
\tt R &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt}  \\
\tt S &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt}  \\
\tt T &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt}  \\
\tt U &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt}  \\
\tt V &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt}  \\
\tt W &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt}  \\
\tt X &\tt X \kern{-5pt} &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt}  \\
\tt Y &\tt Y \kern{-5pt} &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt}  \\
\tt Z &\tt Z \kern{-5pt} &\tt A \kern{-5pt} &\tt B \kern{-5pt} &\tt C \kern{-5pt} &\tt D \kern{-5pt} &\tt E \kern{-5pt} &\tt F \kern{-5pt} &\tt G \kern{-5pt} &\tt H \kern{-5pt} &\tt I \kern{-5pt} &\tt J \kern{-5pt} &\tt K \kern{-5pt} &\tt L \kern{-5pt} &\tt M \kern{-5pt} &\tt N \kern{-5pt} &\tt O \kern{-5pt} &\tt P \kern{-5pt} &\tt Q \kern{-5pt} &\tt R \kern{-5pt} &\tt S \kern{-5pt} &\tt T \kern{-5pt} &\tt U \kern{-5pt} &\tt V \kern{-5pt} &\tt W \kern{-5pt} &\tt X \kern{-5pt} &\tt Y \kern{-5pt}  \\

\end{array}
$$

Vigenère 加密在操作时需要注意：

1. $\circledR$ 运算忽略参与运算的字母的大小写，并保持字母在明文 $M$ 中的大小写形式；
2. 当明文 $M$ 的长度大于密钥 $k$ 的长度时，将密钥 $k$ 重复使用。

例如，明文 $M=\texttt{Helloworld}$，密钥 $k=\texttt{abc}$ 时，密文 $C=\texttt{Hfnlpyosnd}$。

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|c|c|c|c|c|c|} \hline
\textsf{明文} & \tt H & \tt e & \tt l & \tt l & \tt o & \tt w & \tt o & \tt r & \tt l & \tt d \\  \hline
\textsf{密钥} & \tt a & \tt b & \tt c & \tt a & \tt b & \tt c & \tt a & \tt b & \tt c & \tt a \\  \hline
\textsf{密文} & \tt H & \tt f & \tt n & \tt l & \tt p & \tt y & \tt o & \tt s & \tt n & \tt d \\  \hline
\end{array}
$$


## 说明/提示

对于 $100\%$ 的数据，输入的密钥的长度不超过 $100$，输入的密文的长度不超过 $1000$，且都仅包含英文字母。

NOIP 2012 提高组 第一天 第一题

## 样例 #1

### 输入

```
CompleteVictory
Yvqgpxaimmklongnzfwpvxmniytm```

### 输出

```
Wherethereisawillthereisaway```

# 题解

## 作者：ingu (赞：487)


我来发个代码稍短一点的题解。

铺垫一个关于ASCII码的小知识：字母'A'的ASCII码是41H（0100 0001B），字母'a'的ASCII码是61H（0110 0001B），字母'A'与'a'的二进制后5位是相同的，所以无论是大写字母还是小写字母x，x
&31（1 1111B）的值就是x在字母表里的顺序。

开始题解：本题的目的就是问你如何去篡位，例如秘钥k里面的字符'C'代表的就是明文向后篡2位得到密文，反过来已知密文，'C'代表的就是向前篡2位，这样'Y'就得到了'W'。

而篡位是有边界的，就是如果篡过了头，需要再回来，A之后就是Z了。所以需要判断一下密文的和篡位之间的大小，如果篡位大，需要补26.

参考代码：

```
#include <iostream>
using namespace std;
int main() {
	string k,c;
	cin>>k>>c;
	for (int i=0;i<c.length();i++) {
		int t=(k[i%k.length()]&31)-1;
		c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
	}
	cout<<c<<endl;
	return 0;
}

```

---

## 作者：huluobotou (赞：41)

我看了一下，应该没有和我思路一样的

~~如果有就是我眼瞎~~

         ——————>
         
       1 2 3 4..................................26
![](https://cdn.luogu.com.cn/upload/pic/30.png)
## 让我们观察一下这个图

我们把A到Z标为1到26

不难发现，每一个**45度斜**的一行横纵坐标**加和**是一样的

## 我们可以暴力把每一个斜行的**加和**存到一个数组x[]里
```
	for(int i=1;i<=26;i++)
		x[i]=i+1,x[26+i]=i+1+26;
```
左上角的A加和为2，往后依次++

通过观察，发现这个表中从**左上**到**右下**把A~Z遍历一遍后又从A~Y遍历一遍这样就有了x[i]=i+1,x[26+i]=i+1+26

（虽说第二个Z没用，但写了也无妨）

然后用**加密文**中字母所对应的数字找到**x**[]中所对应的加和减去**密钥**字母所对应的数字就是原文本所对应的数字了

再用阿斯克码还原成字母就行了

## 这里还需要一个v[]数组

用来记录**大写字母**

这道题是有大写字母的，对应的原文也得是大写字母，所以要记下来

**PS**：本人阿斯克码弱的一批，所以字符、数字转换麻烦了一些，大佬凑合看吧

AC代码：
```
#include<bits/stdc++.h>
using namespace std;
char a[1010],b[110],c[1010];//存字符， a密文  b密钥  c原文 
int a1[1010],b1[110],c1[1010];//存数字 
bool v[1010];//v[i]为1则c[i]为大写 
int x[60];//存每一斜行加和 
int main()
{
	cin>>b>>a;
	for(int i=1;i<=26;i++)  //预先把加和打好 
		x[i]=i+1,x[26+i]=i+1+26;
	int l=strlen(a),l2=strlen(b);
	for(int i=0;i<l;i++){       //a转化成数字 
		if(a[i]>='a'&&a[i]<='z')
		a1[i]=a[i]-'a'+1;
		else{
			a1[i]=a[i]-'A'+1;
			v[i]=1;
		}	
	}
	for(int i=0;i<l2;i++){    //b转换为数字 
		if(b[i]>='a'&&b[i]<='z')
		b1[i]=b[i]-'a'+1;
		else
		b1[i]=b[i]-'A'+1;
	}
	int n=0;
	for(int i=0;i<l;i++){//作差求原文 
		if(x[a1[i]]>b1[n])//这里为什么要判断一下呢？前面说了，同一字母会在不同斜行中出现两次 
		c1[i]=x[a1[i]]-b1[n];
		else
		c1[i]=x[a1[i]+26]-b1[n];
		n++;
		if(n==l2) n=0;
	}
	for(int i=0;i<l;i++){//再把c转化成字符 
		if(!v[i])
		c[i]=c1[i]-1+'a';
		else
		c[i]=c1[i]-1+'A';
	}
	cout<<c;
	return 0;
}
```

撒花。。


---

## 作者：LightCoder (赞：33)

首先声明，我是**蒟蒻**，第一次写题解，还望各位多多包涵qwq

这里我使用的是打表的方法，**使用Queue打表，简单易懂**，没有复杂的密码反演，也没有冗长的公式计算，打完表后，只需要分析大小写情况写好if，直接查表即可得出答案

------------
# 要点1：解析密码表

分析题目不难发现只要将密码表中的规律解析出来就可以得出答案，所以首先，我想到的第一个办法便是打表

既然是打表，那么我们首先就将密码表看做一个数字矩阵，A~Z分别对应1~26，仔细观察每一行，你就会发现一个有趣的事情

密钥表的第一行：
- A B C D E R G ······· X Y Z

密钥表的第二行：
- B C D E F G H ······· Y Z A

从上面的字母序列我们可以看到这样的规律，就像是将首字母从**队头**取出来，然后把它塞在**队尾**，剩下的字母自动往前顶一位，以此类推。

**取出队头，插入队尾？？？**这不就是Queue队列嘛？？于是我们先初始化队列，队列的初始状态就是A-Z即 1,2,3···25,26 接着使用两个For循环，每一行都进行取出和插入两个操作即可

上代码！
```cpp
#include<queue>  //queue队列必开头文件
std::queue<int> q;  //因为实在懒，所以直接std
int i,j; 
for(i=1;i<=26;i++) q.push(i); //初始化队列顺序
for(i=1;i<=26;i++){
	for(j=1;j<=26;j++){  //这个for循环主要负责将队列遍历一遍来填表，因为queue是没有办法查数据位置的。
		Mid=q.front();   
		Map[i][j]=q.front();
		q.push(Mid);q.pop();
     }
	Mid=q.front();   //以下代码就是将队列进行队头队尾操作，使其能够转换成下一行
	q.push(Mid);q.pop();
} 
```

这个时候，就会有人发现一个问题，原来的密码表：横轴对应的是密文，纵轴对应原文，由此得出密钥,但是我们的已知条件是密钥和密文，求原文，怎么办？？这个时候我们根据已知关系来推出真密码表，只两行你就能能看出规律。

真·密码表第一行：

- A Z Y X W V U T S R Q P O N M L K J I H G F E D C B

真·密码表第二行：

- B A Z Y X W V U T S R Q P O N M L K J I H G F E D C

观察完两行密码表后，依然可以看到大体规律也是相同的，只不过，它更像是**反过来的原密码表**，并且第一行A仍在开头，如何处理这些问题？

首先，既然是倒过来的密码表，那我们就把**For循环倒过来**填表，但是倒过来以后，A也在队尾，那我们就将原处理队头队尾的代码**提前**，就能完成真·密码表的构造。

上代码！
```cpp
#include<queue>
std::queue<int> q;
for(register int i=1;i<=26;i++) q.push(i);
for(register int i=1;i<=26;i++){
	Mid=q.front();			//队头队尾处理提前
	q.push(Mid);q.pop();
	for(register int j=26;j>0;j--){
		Mid=q.front();		//同先前代码
		Map[i][j]=q.front();
		q.push(Mid);q.pop();
	}
} 
```
------------

# 要点二：大小写判断
接下来，进行大小写情况的分类讨论即可：

1. 密文大写，密钥小写

2. 密文大写，密钥大写

3. 密文小写，密钥大写

4. 密文小写，密钥大写

由此即可得到四个if，而判断大小写，使用ASCII码即可。

ASCII Z-90,ASCII码**小于**90的皆为大写，剩下的就交给else吧。

------------

# 要点三：密钥的循环使用
接下来是要最后一个要解决的问题，其实也蛮简单的，查表使用For循环时，将此时使用的key字母对应位置使用**j**来记录，然后每查一次表，就进行j++操作，然后当j**超出密钥的长度**时，及时**归零**即可。

最后，上代码！（代码真的很丑，拜托各位大神别喷……）

```
#include<stdio.h>
#include<queue>
#include<string.h>
int Map[35][35],Mid;
std::queue<int> q;
char Key[1005],Password[1005];
int main(){
	for(int i=1;i<=26;i++) q.push(i);
	for(int i=1;i<=26;i++){
		Mid=q.front();
		q.push(Mid);q.pop();
		for(register int j=26;j>=1;j--){
			Mid=q.front();
			Map[i][j]=q.front();
			q.push(Mid);q.pop();
		}
	} 
	scanf("%s",Key);int LenK=strlen(Key);
	scanf("%s",Password);int LenP=strlen(Password);
	int j=0;
	for(int i=0;i<LenP;i++){
		if(j>LenK-1) j=0;
		if(int(Password[i])<=90){
			if(int(Key[j])<=90){printf("%c",Map[int(Password[i])-64][int(Key[j])-64]+64);j++;}
			else{printf("%c",Map[int(Password[i])-64][int(Key[j])-96]+64);j++;}
		}
		else{
			if(int(Key[j])<=90 {printf("%c",Map[int(Password[i])-96][int(Key[j])-64]+96);j++;}
			else{printf("%c",Map[int(Password[i])-96][int(Key[j])-96]+96);j++;}
		}
	}
	return 0;
}
```


------------

如果你读到了这里，感谢你对本题解的资瓷！！

有问题可评论咨询。

---

## 作者：qhr2023 (赞：4)

## solution

通过观察表格发现，将 $M$ 和 $k$ 忽略大小写后，他们对应位置字母的和对 $26$ 取模就得到 $C$ 的对应位置字母，而给定 $C$ 和 $k$，我们逆过来就可以求出 $M$。

$M$ 大小写与 $C$ 统一，对于循环使用 $k$，用取模就可以解决。

[通过记录](https://hydro.ac/record/6781c81d0880eb209114d1c8)。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
string k, c;
char m (char k, char c) {
	if (k>='a'&&c>='a')
		return (c-k+26)%26+'a';
	else if (k>='a'&&c<='Z')
		return (c-'A'-k+'a'+26)%26+'A';
	else if (k<='Z'&&c>='a')
		return (c-'a'-k+'A'+26)%26+'a';
	else
		return (c-k+26)%26+'A';
}
int main () {
	cin >> k >> c;
	for (int i=0; i<(int)c.size(); ++i) 
		cout << m(k[i%k.size()], c[i]);
	return 0;
}
```

---

## 作者：Sinwind (赞：3)

# 1.分析

0. 规律：规定最左边一列为密匙$(k)$，最上边一行为明文$(m)$，表格中为密文$(c)$。

- 观察密码表可发现，当$c\geq k$时，$m$的是第$c-k$个$($从$0$算起$)$，$m='A'+c-k($若$c$为小写字母，$m='a'+c-k)$；

- 当$c<k$时，$c-k<0$，$c$相对于$k$是字母表的下一轮，故$c$先加上$26$再进行减法运算$(m='A'+c+26-k$或$m='a'+c+26-k)$。

1. $decryption$函数：

- 注意：先将$c,k$**统一转化为大写**。

2. $main$函数：

- 注意：密匙$key\_text$需要重复使用，呈**周期性**，故用**模运算**模拟$(i\%key\_len)$。

# 2.代码

```cpp
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string key_text;	//密匙
string cipher_text;	//密文
int key_len;		//密匙长度
int cipher_len;     //密文长度

//c是密文，k是密匙，返回解密后的明文m
char decryption(char c, char k)
{
	char temp_c = toupper(c);
	char temp_k = toupper(k);
	//从A/a算起
	char m =(isupper(c)) ? 'A' : 'a';
    //A/a后第几个
	m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);

	return m;
}

int main(void)
{
	cin >> key_text;
	cin >> cipher_text;
	
	key_len = key_text.length();
	cipher_len = cipher_text.length();
	
	for(int i = 0; i < cipher_len; i++)
	{
		cout << decryption(cipher_text[i], key_text[i % key_len]);
	}
	
	return 0;
}
```


---

## 作者：Kawaii_qiuw (赞：2)

题面很好理解，不再赘述。

### 解题思路

依题知，明文标号为 $M$，密文标号为 $C$，密钥标号为 $k$。

我们观察运算 $®$ 的规则表可以发现，如果我们将 $A$ 标作 $1$，$B$ 标作 $2$，$C$ 标作 $3$，以此类推，那么 $(M + k) \bmod 26 \to C$。对应的，如果 $C - k \ge 0$，则 $M \to C - k$。反之，$M \to C - k + 26$。

密文位数和密钥位数的对应关系是非常显然的，直接用密文的当前位数取模于密钥的总位数就可以得到密钥的当前位数了。

### 代码

```cpp
#include<iostream>
#include<cstdio>

using namespace std;
char k[110];
char m[1100];
int ks[110];
char ms;
 
int main() {
	cin >> k >> m;
	int j;
    //预处理密钥
	for (j = 0; k[j]; ++j) {
		ks[j] = (k[j] >= 'a' ? k[j] - 'a' : k[j] - 'A');
	}
	for (int i = 0; m[i]; ++i) {
		if (m[i] >= 'a') {
			ms = (m[i] - 'a' - ks[i % j] >= 0 ? m[i] - ks[i % j] : m[i] - ks[i % j] + 26);
		}
		else {
			ms = (m[i] - 'A' - ks[i % j] >= 0 ? m[i] - ks[i % j] : m[i] - ks[i % j] + 26);
		}
		printf("%c", ms);
	}
	return 0;
} 
```

---

## 作者：ShirasuAzusaSaikou (赞：2)

在看题解之前，提示：其实这题就是在算偏移。      
可以再去试试做多一遍。     
*****
假如你看到这，那就是想推导过程咯。    
首先，我们有明文 $M$，密钥 $k$，密文 $C$。     
而从题目可以看到，$c_i$ 从 $m_i$ 和 $k_i$ 中推导而出，然后输入为 $k$ 和 $C$，因此需要反推 $C$，也就是推导 $c_i$ 的表达形式。仔细看表中，对于 $k_i = \texttt{A}$，任何 $c_i \gets m_i$，而对于 $k_i = \texttt{B}$，在 ASCII 码上，任何 $c_i \gets m_i + 1$，除去最后一个 $m_i = \texttt{Z}$ 时为 $c_i \gets \texttt{A}$。    
很容易感觉到需要做经典的加二十六再取模。      
~~提示：建议这里细心做，不然容易出错，别问我咋知道。（逃~~      
注意到这个规律后，我们就能有以下公式：     
$ c_i \gets ch + m_i - k_i , ch \in \text{character}$    
很显然，这里是需要避免 $\texttt{A} - 1$ 之类的问题的，因此公式转为：     
$ c_i \gets ch + ((m_i - k_i + 26) \bmod 26), ch \in \text{character}$      
从题意可得出，密钥 $k$ 的大小写与明文的大小写无关，只需要注意密文 $c_i$ 的大小写。     
因此只需要判断当前的 $c_i \ge \texttt{a}$，则 $ch \gets \texttt{a}$，否则 $ch \gets \texttt{A}$。  
由于存在明文 $M$ 的长度可能大于密钥 $k$ 的长度，因此我们需要额外开一个下标，然后每次循环加一和取模即可。       
以上就是本题的思路。        
代码如下：       
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string k, m;
    cin >> k >> m;
    int kl = k.length(), ml = m.length(), ki = 0;
    for(auto &i : k) i = tolower(i);
    for(int i = 0; i < ml; i++){
        cout <<(char) (((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
        ki = (ki + 1) % kl;
    }
    return 0;
}

```

---

## 作者：123456Zhe (赞：2)

# [P1079 题解](https://www.luogu.com.cn/problem/P1079)

本蒟蒻的第一篇题解。

## 大体思路：

先定义一个密钥 $k$ 的指针变量 $q$，表示密文要减去 $k$ 的第几位。

定义指针变量 $i$，表示密文 $M$ 的第几位。从 $0$ 到 $|M|$（注：$|M|$ 表示 $M$ 的长度。）枚举 $i$，判断 $M_i$ 的大小写，再判断密钥 $k_q$ 的大小写：

* 如果 $k_q$ 为大写，则遍历 $k_q - \texttt A$ 次；
  
* 反之，遍历 $k_q - \texttt a$ 次。
  

在每一次遍历中，$M_i$ 减去 $1$，且：

* 如果 $M_i$ 为大写且 $M_i < \texttt A$ 时，$M_i \gets \texttt Z$；
  
* 如果 $M_i$ 为小写且 $M_i < \texttt a$ 时，$M_i \gets \texttt z$。
  

遍历完之后，变量 $q$ 增加 $1$，如果 $q=|k|$，则 $q \gets 0$。

这样就可以把密文转化为明文。

## 示范代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

string k,s;//定义密钥字符串k和密文字符串s

int main() {

    cin>>k>>s;//输入k和s

    int q=0;//定义指针变量q

    for(int i=0;i<s.size();i++){//遍历密文字符串

        if(s[i]>='A'&&s[i]<='Z'){//判断密文大小写

            int h=k[q]>='A'&&k[q]<='Z'?k[q]-'A':k[q]-'a';//判断密钥大小写，并求出遍历次数

            for(int j=0;j<h;j++){//遍历还原

                s[i]--;

                if(s[i]<'A'){//特判，使变化符合规则

                    s[i]='Z';

                }

            }

        }

        if(s[i]>='a'&&s[i]<='z'){//与上面思路相同

            int h=k[q]>='A'&&k[q]<='Z'?k[q]-'A':k[q]-'a';

            for(int j=0;j<h;j++){

                s[i]--;

                if(s[i]<'a'){

                    s[i]='z';

                }

            }

        }

        q++;//指针指向下一位

        if(q==k.size()){//特判，使指针回到开头

            q=0;

        }

    }

    cout<<s;//输出

    return 0;

} 
```

---

## 作者：Jerry_zpl (赞：2)

思路很简单，只要我们观察题目中最下面的表格就可以知道。一个字符串的第 $i$ 项加上密钥的第 $i$ 项所对应的字母表中的第 $x$ 个字符（加上 $x$）得到的就是我们加密后的字符串。所以我们可以定义一个指针 $j$，表示明文的第 $i$ 个字符要加上 $k_j$，然后再注意一下大小写即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	string k;
	string c;
	cin>>k>>c;
	int now=0; 
	for(int i=0;i<c.size();i++)
	{
		char ch=k[now];
		int a;
		if(ch>='A'&&ch<='Z') a=ch-'A';
		if(ch>='a'&&ch<='z') a=ch-'a';
		char b=c[i]-a;
		if(c[i]>='A'&&c[i]<='Z')
		{
			if(b<'A') 
			{
				b+=26; 
			}
		}           
		if(c[i]>='a'&&c[i]<='z')
		{
			if(b<'a') 
			{
				b+=26;
			}		
		}
		cout<<b;
		now++;
		if(now>k.size()-1) now=0;//如果指针超过了长度就回到第0个字符
	}
	return 0;
}
```

---

## 作者：sjh0626 (赞：1)

## 思路分析
根据题意，密文为 $C$，密钥为 $k$，明文为 $M$。

我们可以根据转换公式 $(C_i-k_i+26)\bmod26$ 来得出 $M_i$ 在二十六个字母中的下标。

但是 $k_i$ 和 $C_i$ 有大写有小写，所以要特判。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
using namespace std;
string a,k;
int main(){
	cin>>k>>a;
    for(int i=0;i<a.size();i++){
        k[i%int(k.size())]=char(isupper(a[i])?toupper(k[i%int(k.size())]):tolower(k[i%int(k.size())]));
        a[i]=char((a[i]-k[i%int(k.size())]+26)%26+(isupper(a[i])?'A':'a'));
    }
    cout<<a;
	sjh0626s code;
}
```

---

## 作者：HuangBarry (赞：1)

设密文字符串为 $s$，密钥字符串为 $k$，明文字符串为 $t$。  
从样例可得出，密文字母的大小写和明文字母的大小写是一样的。  
阅读题面后可轻松得出解密的公式为 $t_i=(s_i-k_i+26)\bmod 26$，然后根据题目中所给的表格映射出对应的明文字母后，写入代码即可。\
注意：若密文的长度大于密钥的长度，那么密钥需要重复使用。\
代码如下：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define stl_priority_queue std::priority_queue
#define pbds_priority_queue __gnu_pbds::priority_queue
#define to_string std::to_string
#define endl '\n'
#define Endl cout<<endl
#define Made return
#define by 0
#define Barry +0
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
string k,s,ans="";
int main(){
    //Freopen("filename");
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>k>>s;
    int lenk=k.size(),lens=s.size();
    for(int i=0;i<lens;i++)
        ans+='a'-(s[i]>='A'&&s[i]<='Z')*32+(((s[i]-(s[i]>='a'?'a':'A'))-(k[i%lenk]-(k[i%lenk]>='a'?'a':'A'))+26)%26);
    cout<<ans<<endl;
    Made by Barry;
}

```

---

## 作者：turin_lk (赞：1)

## 1.思路
可以把字母编号：`a` 的编号是 $0$，`b` 的编号是 $1$，以此类推。然后根据题目中的表格，不难看出， $($ 明文字母编号 $+$ 密钥字母编号 $)$ 对 $26$ 取模的值 $=$ 密文字母编号。  
例如 `e` 的编号是 $4$，`n` 的编号是 $13$，所以明文是 `e`，密钥是 `n` 的时候，密文是 $(5+13)\bmod 26 = 18$，$18$ 对应的字母是 `r`，所以密文是 `r`。  
如果倒推一下，就得出密文字母编号 $-$ 密钥字母编号 $=$ 明文字母编号，可能会减出负数，这时就需要加上 $26$。再把大小写记录一下，最后把记录结果和编号相加，就得出了明文字母。  
还是刚才的例子，明文是 `r`，密钥是 `n` 的时候，明文是 $18 - 13 = 5$，$5$ 对应的字母是 `e`，所以明文字母是 `e`。
## 2.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string mw,my;
int t;//记录大小写的变量
int main()
{
	cin>>my>>mw;
	for(int i=0;i<mw.size();i++)
	{
		t=0;
		if(my[i%my.size()]>='a'&&my[i%my.size()]<='z')//i%my.size()表示密文的第i项对应着密钥的第几项
		{
			my[i%my.size()]-=32;
		}
		if(mw[i]>='a'&&mw[i]<='z')
		{
			mw[i]-=32;
			t=1;
		}
		if(mw[i]<my[i%my.size()])mw[i]+=26;
		mw[i]-=my[i%my.size()];
		if(t==1) mw[i]+=32;
	}
	for(int i=0;i<mw.size();i++)
	{
		cout<<char(mw[i]+65);
	}
	return 0;
}
```

---

## 作者：ridewind2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1079)

## 思路

![](https://cdn.luogu.com.cn/upload/pic/30.png)

两个字符串长度不同，所以要将它们统一长度，都统一成长度较长的字符串的长度：


```cpp
int n=k.size(),m=s.size();
if(n<m)for(int i=n;i<m;i++)k.push_back(k[i%n]);
else for(int i=m;i<n;i++)s.push_back(s[i%m]);
```


然后，我们要开始解密了，由于我们已经统一长度了，所以直接用其中一个字符串的长度循环即可。根据图片，我们发现 ```m[i]+k[i]-'A'=c[i]```，所以，```(c[i]-k[i]+26)%26+'A'=m[i]```（取模前要加 $26$，因为可能出现负数），所以，我们写出以下代码：

```cpp

for(int i=0;i<k.size();i++){
		if(c[i]<='Z'&&c[i]>='A'){
			if(k[i]<='Z'&&k[i]>='A'){
				cout<<(char)((c[i]-k[i]+26)%26+'A');
			}else{
				cout<<(char)((c[i]-'A'-k[i]+'a'+26)%26+'A');
			}
		}else{
			if(k[i]<='Z'&&k[i]>='A'){
				cout<<(char)((c[i]-'a'-k[i]+'A'+26)%26+'a');
			}else{
				cout<<(char)((c[i]-k[i]+26)%26+'a');
			}
		}
	}

```

## AC Code

```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
	string k,c;
	cin>>k>>c;
	int n=k.size(),m=c.size();
	if(n<m)for(int i=n;i<m;i++)k.push_back(k[i%n]);
	else for(int i=m;i<n;i++)c.push_back(c[i%m]);
	for(int i=0;i<k.size();i++){
		if(c[i]<='Z'&&c[i]>='A'){
			if(k[i]<='Z'&&k[i]>='A'){
				cout<<(char)((c[i]-k[i]+26)%26+'A');
			}else{
				cout<<(char)((c[i]-'A'-k[i]+'a'+26)%26+'A');
			}
		}else{
			if(k[i]<='Z'&&k[i]>='A'){
				cout<<(char)((c[i]-'a'-k[i]+'A'+26)%26+'a');
			}else{
				cout<<(char)((c[i]-k[i]+26)%26+'a');
			}
		}
	}
	return 0;
}

```

---

## 作者：3_14 (赞：0)

[**题目传送门**](https://www.luogu.com.cn/problem/P1079)

# 思路

解密过程与加密过程类似，只是操作的方向相反。具体来说，给定密文 $C$ 和密钥 $k$，我们需要通过逆向操作来恢复明文。

解密步骤：
* 密钥重复：如果密文的长度大于密钥的长度，密钥需要重复使用。
* 解密操作：对于密文中的每个字符 $C_i$ 和对应的密钥字符 $k_i$，通过逆向操作得到明文字符 $m_i$。

  * 如果密文字符是大写字母，明文字符也是大写字母。
  * 如果密文字符是小写字母，明文字符也是小写字母。

所以解密的公式为 $m_i=\left(C_i-k_i+26\right)\bmod 26$，然后根据字母表映射回对应的字母。

# 代码


```cpp
#include<bits/stdc++.h>
#define Freopen(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define lcm(x,y) x/__gcd(x,y)*y;
#define lb(x) (x&-x)
#define str to_string
#define Made return
#define by 0
#define _3_14 ;
using namespace std;
using ll=long long;
const double EPS=1e-6,PAI=acos(-1.0);
const int MAX=1e3+1;
// 将字符转换为0-25的数字
int charToNum(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return 0; // 非字母字符处理
}
// 将数字转换为字符
char numToChar(int num, bool isUpper) {
    if (isUpper) {
        return 'A' + num;
    } else {
        return 'a' + num;
    }
}
string vigenereDecrypt(const string& ciphertext, const string& key) {
    string plaintext;
    int keyLength = key.length();
    int ciphertextLength = ciphertext.length();
    for (int i = 0; i < ciphertextLength; ++i) {
        char c = ciphertext[i];
        bool isUpper = (c >= 'A' && c <= 'Z');
        int cNum = charToNum(c);
        int kNum = charToNum(key[i % keyLength]);
        // 解密公式：m_i = (c_i - k_i + 26) % 26
        int mNum = (cNum - kNum + 26) % 26;
        char m = numToChar(mNum, isUpper);

        plaintext.push_back(m);
    }
    return plaintext;
}
int main() {
    string key, ciphertext;
    cin >> key >> ciphertext;
    string plaintext = vigenereDecrypt(ciphertext, key);
    cout << plaintext << endl;
	Made by _3_14
}
```

[**AC 记录**](https://www.luogu.com.cn/record/197645527)

---

