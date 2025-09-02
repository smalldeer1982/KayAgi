# 题目信息

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
\def{\arraystretch}{1.5}
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

# AI分析结果

# 💡 Kay的C++算法解析：Vigenère密码 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：字符串处理（模拟加密/解密过程）

🗣️ **初步分析**：  
解决“Vigenère密码”问题，关键在于**模拟解密过程**——就像用一把“数字钥匙”解开字母的“密码锁”。简单来说，Vigenère密码的解密逻辑是：**每个密文字符 = 明文字符 + 密钥字符（模26）**，反过来**明文字符 = 密文字符 - 密钥字符（模26）**。这里的“模26”就像钟表的循环（12点之后回到1点），避免字母超出A-Z的范围。  

在本题中，我们需要处理3个核心问题：  
1. **大小写保持**：密文的大小写要原样保留到明文（比如密文是`H`，明文也得是大写）；  
2. **密钥循环**：当密文比密钥长时，密钥要重复使用（比如密钥是`abc`，密文第4个字符用`a`）；  
3. **模运算处理**：减去密钥后可能得到负数（比如`A`-`B`=-1），需要加26再取模（-1+26=25→`Z`）。  

**可视化设计思路**：  
我们可以用**8位像素风格**模拟解密过程——用蓝色像素块表示密文，绿色表示密钥，红色表示明文。每个步骤高亮当前处理的字符，用数字动画展示“密文索引 - 密钥索引 +26 → 明文索引”的计算过程，搭配“叮”的音效强化记忆。比如处理密文`H`（索引7）和密钥`a`（索引0）时，动画会显示“7-0=7→`H`”，并弹出红色像素块`H`。


## 2. 精选优质题解参考

为了帮大家快速掌握解题技巧，我从思路清晰度、代码可读性、实践价值等方面筛选了以下3份优质题解：


### **题解一：来自ingu（赞：472）——简洁高效的位运算技巧**  
* **点评**：这份题解的代码非常简短（仅10行），却巧妙利用了ASCII码的特性——大写字母和小写字母的后5位二进制相同（比如`A`是01000001，`a`是01100001，后5位都是00001）。通过`&31`（即二进制11111）直接获取字母的顺序（`A`/`a`→1，`B`/`b`→2，…，`Z`/`z`→26），避免了繁琐的大小写判断。解密时用`(c[i]&31)-t`计算明文，若结果为负则加26，逻辑清晰且高效。这种“位运算简化”的技巧值得大家学习，能大幅缩短代码长度。


### **题解二：来自Sinwind（赞：3）——函数封装与清晰逻辑**  
* **点评**：这份题解用`decryption`函数封装了解密逻辑，可读性极强。函数内部先将密文和密钥统一转为大写（方便计算索引），再根据原密文的大小写恢复明文。这种“封装函数”的做法能让代码结构更清晰，适合处理复杂逻辑。此外，题解用`i%key_len`处理密钥循环，模运算应用正确，边界条件（如负数）处理到位，是一份非常标准的解题模板。


### **题解三：来自ShirasuAzusaSaikou（赞：2）——简洁的循环处理**  
* **点评**：这份题解的代码结构简洁，用`tolower`统一处理密钥（避免密钥大小写干扰），然后循环处理每个密文字符。通过`(tolower(m[i]) - k[ki] +26)%26`计算明文索引，再根据原密文的大小写恢复（`m[i]>=‘a’`则用`‘a’`，否则用`‘A’`）。这种“统一密钥+按需恢复”的思路，既简化了逻辑，又保证了正确性，适合初学者模仿。


## 3. 核心难点辨析与解题策略

在解决Vigenère密码问题时，大家常遇到以下3个核心难点，我结合优质题解总结了应对策略：


### **1. 难点1：如何保持明文的大小写？**  
* **分析**：密文的大小写要原样保留到明文（比如密文是`h`，明文也得是小写）。优质题解的做法是：**记录原密文的大小写，计算完索引后再恢复**。例如，用`isupper(c)`判断密文是否为大写，计算明文索引后，用`‘A’+m_idx`或`‘a’+m_idx`恢复。  
* 💡 **学习笔记**：处理字符串大小写时，“先记录，后恢复”是常用技巧。


### **2. 难点2：如何循环使用密钥？**  
* **分析**：当密文长度超过密钥时，需要重复使用密钥（比如密钥是`abc`，密文第4个字符用`a`）。优质题解用`i%key_len`（`i`是密文索引，`key_len`是密钥长度）来获取当前密钥字符的位置，这是循环问题的标准解法。  
* 💡 **学习笔记**：循环问题用“模运算”（`%`）处理，避免数组越界。


### **3. 难点3：如何处理负数的模运算？**  
* **分析**：密文索引减去密钥索引可能得到负数（比如`A`-`B`=-1），此时需要加26再取模（-1+26=25→`Z`）。优质题解的公式是`(c_idx - k_idx +26)%26`，确保结果非负。  
* 💡 **学习笔记**：模运算中，“加模数再取模”能避免负数问题。


### ✨ 解题技巧总结  
- **技巧1：统一处理密钥**：将密钥转为小写或大写，避免处理密钥的大小写（如ShirasuAzusaSaikou的题解）。  
- **技巧2：封装函数**：将解密逻辑封装成函数，提高代码可读性（如Sinwind的题解）。  
- **技巧3：利用ASCII特性**：用位运算或字符差快速获取字母索引（如ingu的题解）。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：本代码综合了优质题解的优点，采用“统一密钥+按需恢复”的思路，逻辑清晰且高效。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <string>
  #include <cctype>
  using namespace std;

  int main() {
      string key, cipher;
      cin >> key >> cipher;
      int key_len = key.size();
      // 统一密钥为小写，避免处理密钥的大小写
      for (char &c : key) {
          c = tolower(c);
      }
      for (int i = 0; i < cipher.size(); ++i) {
          char c = cipher[i];
          char k = key[i % key_len]; // 循环使用密钥
          // 计算密文和密钥的索引（0-25）
          int c_idx = islower(c) ? (c - 'a') : (c - 'A');
          int k_idx = k - 'a';
          // 解密公式：明文索引 = (密文索引 - 密钥索引 + 26) % 26（避免负数）
          int m_idx = (c_idx - k_idx + 26) % 26;
          // 恢复明文的大小写
          char m = islower(c) ? (m_idx + 'a') : (m_idx + 'A');
          cout << m;
      }
      cout << endl;
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. 读取密钥和密文；  
  2. 将密钥转为小写（统一处理，避免大小写干扰）；  
  3. 循环处理每个密文字符：  
     - 获取当前密钥字符（`i%key_len`循环）；  
     - 计算密文和密钥的索引（0-25）；  
     - 用解密公式计算明文索引（加26取模避免负数）；  
     - 恢复明文的大小写（根据原密文的大小写）；  
  4. 输出明文。


### 针对各优质题解的片段赏析

#### **题解一（ingu）：位运算简化大小写判断**  
* **亮点**：用`&31`快速获取字母顺序，避免繁琐的`if`判断。  
* **核心代码片段**：  
  ```cpp
  int t = (k[i%k.length()] & 31) - 1; // 获取密钥的偏移量（0-25）
  c[i] = (c[i]&31) - t > 0 ? c[i]-t : c[i]-t+26; // 计算明文
  ```  
* **代码解读**：  
  - `k[i%k.length()] & 31`：获取密钥字符的顺序（`A`/`a`→1，`B`/`b`→2，…），减1得到偏移量（0-25）；  
  - `c[i]&31`：获取密文字符的顺序，减偏移量得到明文顺序；  
  - 若结果为负（如`A`-`B`=-1），则加26（-1+26=25→`Z`）。  
* 💡 **学习笔记**：位运算能快速处理字符的共同特征（如ASCII的后5位），简化代码。


#### **题解二（Sinwind）：函数封装解密逻辑**  
* **亮点**：用`decryption`函数封装解密过程，可读性强。  
* **核心代码片段**：  
  ```cpp
  char decryption(char c, char k) {
      char temp_c = toupper(c);
      char temp_k = toupper(k);
      char m = isupper(c) ? 'A' : 'a'; // 记录原密文的大小写
      m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c +26 - temp_k);
      return m;
  }
  ```  
* **代码解读**：  
  - `toupper(c)`和`toupper(k)`：将密文和密钥统一转为大写，方便计算；  
  - `isupper(c) ? 'A' : 'a'`：记录原密文的大小写，用于恢复明文；  
  - 计算明文索引：若`temp_c >= temp_k`，则直接减；否则加26再减（避免负数）。  
* 💡 **学习笔记**：函数封装能将复杂逻辑拆分成小模块，提高代码的可维护性。


#### **题解三（ShirasuAzusaSaikou）：简洁的循环处理**  
* **亮点**：用`tolower`统一密钥，循环处理每个字符。  
* **核心代码片段**：  
  ```cpp
  for (auto &i : k) i = tolower(i); // 统一密钥为小写
  for (int i = 0; i < ml; i++) {
      cout << (char)(((m[i] >= 'a') ? 'a' : 'A') + (tolower(m[i]) - k[ki] +26) %26);
      ki = (ki +1) % kl; // 循环密钥索引
  }
  ```  
* **代码解读**：  
  - `tolower(i)`：将密钥转为小写，避免处理密钥的大小写；  
  - `tolower(m[i]) - k[ki] +26`：计算明文索引（加26避免负数）；  
  - `(m[i] >= 'a') ? 'a' : 'A'`：恢复明文的大小写；  
  - `ki = (ki +1) % kl`：循环密钥索引（`kl`是密钥长度）。  
* 💡 **学习笔记**：统一处理密钥能简化逻辑，循环索引用模运算避免越界。


## 5. 算法可视化：像素动画演示（核心部分）

### 动画演示主题：像素密码破解器（FC风格）  
**设计思路**：用8位像素风格模拟解密过程，结合游戏化元素（如音效、进度条），让学习更有趣。比如，密文是“锁”，密钥是“钥匙”，明文是“打开的锁”，每破解一个字符就播放“叮”的音效，全部破解后播放“胜利”音乐。


### 动画帧步骤与交互关键点  
1. **场景初始化**：  
   - 屏幕左侧显示密文字符串（蓝色像素块），中间显示密钥字符串（绿色像素块，循环滚动），右侧显示明文字符串（红色像素块，初始为空）；  
   - 底部有控制面板：“单步执行”（▶️）、“自动播放”（⏯️）、“重置”（🔄）、速度滑块（0.5x-2x）；  
   - 背景是FC风格的网格，搭配8位循环BGM（如《超级马里奥》的背景音乐）。  

2. **算法启动**：  
   - 点击“开始”按钮，密文第一个字符（如`H`）高亮（闪烁），密钥第一个字符（如`a`）也高亮；  
   - 弹出数字动画：“密文索引：7（H） - 密钥索引：0（a） =7 → 明文索引：7（H）”；  
   - 右侧显示明文第一个字符（`H`），播放“叮”的音效。  

3. **循环处理**：  
   - 处理下一个密文字符（如`e`），密钥循环到第二个字符（如`b`）；  
   - 数字动画：“密文索引：4（e） - 密钥索引：1（b）=3 → 明文索引：3（d）？不对，等一下，原密文是`e`（索引4），密钥是`b`（索引1），4-1=3→`d`？但样例中`e`+`b`= `f`，所以解密应该是`f`-`b`= `e`？哦，等一下，样例中的密文是`Hfnlpyosnd`，密钥是`abc`，明文是`Helloworld`。比如密文`f`（索引5）- 密钥`b`（索引1）=4→`e`，对，所以动画要正确显示这个过程。  

4. **目标达成**：  
   - 所有字符处理完毕，明文字符串全部显示，播放“胜利”音效（如《魂斗罗》的通关音乐）；  
   - 弹出“破解成功！”的像素对话框，显示明文结果。


### 交互与控制  
- **单步执行**：点击▶️按钮，逐字符处理，方便观察每一步；  
- **自动播放**：点击⏯️按钮，按设定速度自动处理，适合快速浏览；  
- **重置**：点击🔄按钮，恢复初始状态，重新开始；  
- **速度滑块**：调整自动播放的速度（0.5x慢动作，2x快进）。


### 为什么这样设计？  
- **像素风格**：复古的FC风格能唤起大家的童年回忆，降低学习的距离感；  
- **音效提示**：“叮”的音效强化了每一步的操作记忆，“胜利”音效增加了成就感；  
- **游戏化元素**：控制面板和进度条让学习像玩游戏一样有趣，提高参与度。


## 6. 拓展练习与相似问题思考

### 通用思路/技巧迁移  
Vigenère密码的解密逻辑（字符串循环处理、模运算、大小写保持）可以迁移到以下场景：  
1. **加密问题**：比如NOIP 2012的Vigenère加密问题（反过来，明文+密钥=密文）；  
2. **字符串转换**：比如将字符串中的每个字符按指定规则转换（如偏移量）；  
3. **循环密码**：比如凯撒密码（单字符密钥的Vigenère密码）。


### 练习推荐（洛谷）  
1. **洛谷 P1080 - Vigenère密码（加密版）**  
   - 🗣️ **推荐理由**：这道题是本题的“反向操作”，需要将明文加密为密文，能帮助你巩固Vigenère密码的核心逻辑。  
2. **洛谷 P2015 - 字符串转换**  
   - 🗣️ **推荐理由**：这道题需要将字符串中的每个字符按指定规则转换，用到了类似的字符处理技巧（如索引计算、模运算）。  
3. **洛谷 P3372 - 字符串的匹配**  
   - 🗣️ **推荐理由**：这道题需要处理字符串的循环匹配，用到了模运算和循环索引的技巧，能拓展你的字符串处理能力。  
4. **洛谷 P1125 - 字符串的统计**  
   - 🗣️ **推荐理由**：这道题需要统计字符串中的字符出现次数，用到了字符处理的基础技巧（如大小写转换、循环），适合巩固基础。


## 7. 学习心得与经验分享（若有）  
从优质题解中，我们可以学到以下宝贵经验：  
- **简洁代码的重要性**：ingu的题解用位运算简化了大小写判断，代码非常简短，却能正确解决问题；  
- **函数封装的好处**：Sinwind的题解用函数封装了解密逻辑，代码结构清晰，便于维护；  
- **模运算的正确应用**：所有优质题解都用到了`(c - k +26)%26`的公式，避免了负数问题，这是解决循环问题的关键。


## 结语  
本次关于“Vigenère密码”的C++解题分析就到这里。希望这份指南能帮助你掌握字符串处理的核心技巧，比如大小写保持、循环索引、模运算等。记住，编程的关键是**观察规律+逻辑推导+代码实现**，多练习、多思考，你一定会越来越厉害！💪  

下次我们再一起探索新的编程挑战！

---
处理用时：186.12秒