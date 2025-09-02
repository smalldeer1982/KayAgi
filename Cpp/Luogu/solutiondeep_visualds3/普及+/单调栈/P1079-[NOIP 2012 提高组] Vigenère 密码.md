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

# AI分析结果

# 💡 Kay的C++算法解析：Vigenère密码 深入学习指南 💡

今天我们来一起分析NOIP2012提高组的经典题目——**Vigenère密码**。这道题虽然看起来涉及“密码学”，但本质是**字符串模拟**的基础应用，核心是“按规则逆向推导”。通过这道题，我们能学会如何处理字符串的循环、大小写转换和模运算，这些都是编程中的高频技巧！


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟（字符串处理+规则逆向推导）

🗣️ **初步分析**：  
Vigenère密码的解密过程，就像“把被推走的积木拉回来”——密文字符是被密钥“推”过的结果，我们要根据密钥的“推力”（偏移量）把它拉回原来的位置。具体来说：  
- **核心规则**：忽略密钥的大小写，用密钥的每个字符计算“偏移量”（比如'A'是0，'B'是1，…，'Z'是25）；然后将密文字符**减去这个偏移量**，如果结果小于'A'（或'a'），就加26“绕回来”；最后保持明文的大小写与密文一致。  
- **密钥循环**：如果密文比密钥长，就重复使用密钥（比如密钥是"abc"，密文第4位对应密钥第1位）。  

**核心算法流程**：  
1. 读入密钥`k`和密文`c`；  
2. 遍历密文的每个字符`c[i]`，找到对应的密钥字符`k[i%k.length()]`（循环使用）；  
3. 计算密钥的偏移量（忽略大小写，转为0-25的数字）；  
4. 密文字符减去偏移量，处理负数（加26），保持大小写；  
5. 输出所有明文字符。  

**可视化设计思路**：  
我会用**8位像素风**模拟这个过程——屏幕分成三个区域：左边是密文（红色像素块）、中间是当前使用的密钥（蓝色像素块）、右边是明文（绿色像素块）。每个步骤会**高亮当前处理的字符**（比如闪烁），并显示偏移量计算（比如“密文'H' - 密钥'a'(0) → 'H'”）。同时加入音效：处理每个字符时播放“叮”的像素声，全部完成时播放“胜利音效”，让你直观“看”到解密的每一步！


## 2. 精选优质题解参考

为了帮大家找到最清晰、最实用的解法，我从**思路清晰度、代码简洁性、技巧实用性**三个维度筛选了3份优质题解：


### 题解一：作者ingu（赞：487）
* **点评**：这份题解的最大亮点是**用ASCII码技巧简化计算**——作者发现大写字母（'A'-'Z'）和小写字母（'a'-'z'）的二进制后5位相同（比如'A'是01000001，'a'是01100001，后5位都是00001），所以用`x&31`能直接得到字符在字母表中的顺序（'A'→1，'B'→2，…，'Z'→26）。代码只有8行，却完美覆盖了所有规则，是“用技巧简化代码”的典范！


### 题解二：作者Sinwind（赞：3）
* **点评**：这份题解的优势是**思路结构化**——作者把解密逻辑封装成`decryption`函数，明确区分“大小写判断”“偏移量计算”“绕回处理”三个步骤，可读性极强。尤其是“统一将密文和密钥转为大写计算，再恢复大小写”的方法，避免了复杂的条件判断，非常适合新手学习！


### 题解三：作者3_14（赞：0）
* **点评**：这份题解的亮点是**模块化编程**——作者写了`charToNum`（字符转0-25数字）和`numToChar`（数字转字符）两个辅助函数，把“字符与数字的转换”从主逻辑中分离出来，让代码更清晰。这种“拆分复杂问题”的思路，在处理大型项目时非常有用！


## 3. 核心难点辨析与解题策略

在解密过程中，大家最容易卡壳的三个点是：**密钥循环**、**大小写处理**、**偏移量计算**。结合优质题解，我总结了对应的解决策略：


### 1. 关键点1：如何循环使用密钥？
* **问题**：密文长度可能远大于密钥，如何重复使用密钥？  
* **解决策略**：用**模运算**！对于密文的第`i`位，对应的密钥位是`i%k.length()`（比如密钥长度是3，i=3时对应0位，i=4对应1位，以此类推）。  
* 💡 **学习笔记**：模运算=“循环计数器”，是处理“重复使用”问题的神器！


### 2. 关键点2：如何保持明文的大小写？
* **问题**：密文有大小写，密钥也有大小写，但明文要和密文大小写一致，密钥的大小写不影响结果。  
* **解决策略**：  
  - 密钥：不管大小写，统一转为0-25的偏移量（比如'A'和'a'都转成0）；  
  - 密文：记录当前字符是大写还是小写，计算完成后恢复大小写（比如密文是'H'→大写，结果转成'A'+偏移；密文是'h'→小写，结果转成'a'+偏移）。  
* 💡 **学习笔记**：“先记录状态，再处理逻辑，最后恢复状态”是处理“保留原始属性”问题的通用方法！


### 3. 关键点3：如何处理偏移量的负数？
* **问题**：密文字符减去偏移量可能小于'A'（比如密文是'A'，偏移量是1，结果是'@'，这显然不对）。  
* **解决策略**：**加26再模26**！比如`(c_num - k_num + 26) % 26`，这样即使结果是负数（比如0-1=-1），加26后变成25，模26还是25，对应'Z'，正好是正确结果。  
* 💡 **学习笔记**：模运算+补数，是处理“循环边界”问题的关键！


### ✨ 解题技巧总结
1. **ASCII码技巧**：用`x&31`快速获取字母顺序（适用于大小写字母）；  
2. **函数封装**：把重复逻辑（比如字符转数字）写成函数，让主代码更简洁；  
3. **边界处理**：用`+26`避免负数，用模运算处理循环。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
* **说明**：综合了Sinwind和3_14的思路，兼顾清晰性和简洁性，适合新手直接学习。
* **完整核心代码**：
```cpp
#include <iostream>
#include <string>
#include <cctype>  // 包含toupper、tolower函数

using namespace std;

// 解密单个字符：c是密文，k是密钥，返回明文
char decrypt(char c, char k) {
    // 1. 计算密钥的偏移量（忽略大小写，转为0-25）
    int k_offset = toupper(k) - 'A';
    // 2. 计算密文的数字值（保留大小写）
    bool is_upper = isupper(c);
    int c_num = toupper(c) - 'A';
    // 3. 解密计算：(密文 - 偏移量 + 26) % 26
    int m_num = (c_num - k_offset + 26) % 26;
    // 4. 恢复大小写
    return is_upper ? ('A' + m_num) : ('a' + m_num);
}

int main() {
    string key, cipher;
    cin >> key >> cipher;
    int key_len = key.length();
    // 遍历密文，逐个解密
    for (int i = 0; i < cipher.length(); ++i) {
        // 循环使用密钥：i%key_len获取当前密钥字符
        char k_char = key[i % key_len];
        cout << decrypt(cipher[i], k_char);
    }
    return 0;
}
```
* **代码解读概要**：  
  - 辅助函数`decrypt`负责单个字符的解密，处理了**大小写判断**、**偏移量计算**、**边界处理**三个核心步骤；  
  - 主函数读入密钥和密文，用`i%key_len`循环使用密钥，逐个输出明文字符。


### 针对各优质题解的片段赏析

#### 题解一：作者ingu的核心代码片段
* **亮点**：用`&31`简化字母顺序计算，代码极致简洁。
* **核心代码片段**：
```cpp
for (int i=0;i<c.length();i++) {
    int t=(k[i%k.length()]&31)-1;  // k的偏移量（&31得到1-26，减1转成0-25）
    c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;  // 解密计算
}
```
* **代码解读**：  
  - `k[i%k.length()]&31`：不管k是大写还是小写，`&31`后得到1-26（比如'A'→1，'a'→33&31=1），减1转成0-25的偏移量；  
  - `(c[i]&31)-t>0`：判断密文减去偏移量后是否大于0（即不小于'A'），否则加26绕回。  
* 💡 **学习笔记**：`&31`是处理大小写字母的“黑科技”，但要注意它的原理（二进制后5位相同）！


#### 题解二：作者Sinwind的核心代码片段
* **亮点**：用函数封装解密逻辑，思路清晰。
* **核心代码片段**：
```cpp
char decryption(char c, char k) {
    char temp_c = toupper(c);
    char temp_k = toupper(k);
    char m = isupper(c) ? 'A' : 'a';  // 记录大小写
    m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);
    return m;
}
```
* **代码解读**：  
  - `toupper(c)`和`toupper(k)`：统一转为大写计算，避免大小写干扰；  
  - `temp_c >= temp_k`：判断是否需要加26（如果密文数字值小于密钥，就加26绕回）；  
  - `m += ...`：计算明文字符的数字值，再恢复大小写。  
* 💡 **学习笔记**：函数封装能让代码“模块化”，即使逻辑复杂，也能一目了然！


#### 题解三：作者3_14的核心代码片段
* **亮点**：用辅助函数拆分字符与数字的转换，可读性强。
* **核心代码片段**：
```cpp
int charToNum(char c) {
    if (isupper(c)) return c - 'A';
    else if (islower(c)) return c - 'a';
    return 0;
}

char numToChar(int num, bool isUpper) {
    return isUpper ? ('A' + num) : ('a' + num);
}
```
* **代码解读**：  
  - `charToNum`：把字符转为0-25的数字（忽略大小写）；  
  - `numToChar`：把数字转为字符（根据`isUpper`恢复大小写）。  
* 💡 **学习笔记**：拆分重复逻辑，能让主代码更简洁，也更容易调试！


## 5. 算法可视化：像素动画演示 (核心部分)

### 动画演示主题：像素解密机
我们用**FC红白机风格**（8位像素、复古色彩）模拟解密过程，让你像玩游戏一样理解算法！


### 设计思路
- **风格**：采用FC的经典配色（比如密文用红色，密钥用蓝色，明文用绿色），字体用像素字，背景是浅灰色网格。  
- **交互**：支持“单步执行”“自动播放”“重置”，速度滑块可以调节动画快慢。  
- **游戏化元素**：每解密一个字符，播放“叮”的像素声；解密完成后，明文区域闪烁并播放“胜利音效”（类似《超级玛丽》的通关声）。


### 动画帧步骤
1. **初始化界面**：  
   屏幕分为三列：左列是密文（红色像素块，每个字符占3x5像素），中列是当前密钥（蓝色像素块），右列是明文（灰色占位符）。底部有控制面板（按钮+速度滑块）。  
2. **单步执行**：  
   - 高亮当前处理的密文字符（红色闪烁）；  
   - 显示对应的密钥字符（蓝色闪烁）；  
   - 弹出小窗口显示计算过程（比如“密文'H' → 7，密钥'a' → 0 → 7-0=7 → 'H'”）；  
   - 右列的明文块变成绿色，显示结果。  
3. **自动播放**：  
   按设定速度依次处理所有字符，每步播放“叮”声，完成后播放胜利音效，明文区域全亮。


### 为什么这么设计？
- **颜色区分**：用红/蓝/绿明确区分密文、密钥、明文，让你一眼看清每个步骤的对象；  
- **音效反馈**：声音能强化记忆，比如“叮”声对应“处理一个字符”，胜利音效对应“完成解密”；  
- **交互控制**：单步执行让你能仔细看每个步骤，自动播放让你快速看整体流程。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
Vigenère密码的解密思路（**循环处理+规则模拟+边界处理**）能解决很多字符串问题，比如：
1. **凯撒密码**：密钥是固定偏移量（比如所有字符加3），解密时减3；  
2. **字母频率统计**：统计字符串中每个字母出现的次数（循环遍历+计数）；  
3. **字符串替换**：用指定规则替换字符（比如把'A'换成'Z'，'B'换成'Y'）。


### 洛谷练习推荐
1. **洛谷 P1598 垂直柱状图**  
   - 🗣️ **推荐理由**：练习字符串的统计与输出，需要处理字符的循环和计数，类似Vigenère密码的“逐个处理”思路。  
2. **洛谷 P2580 于是他错误的点名开始了**  
   - 🗣️ **推荐理由**：练习字符串的查找与匹配，需要处理大量字符串的循环比较，巩固“循环使用”的技巧。  
3. **洛谷 P3741 honoka的键盘**  
   - 🗣️ **推荐理由**：练习字符串的规则转换，需要根据给定规则修改字符，类似Vigenère密码的“按规则推导”思路。


## 7. 学习心得与经验分享 (若有)

### 来自题解作者的经验
- **作者ingu**：“字母'A'和'a'的二进制后5位相同，所以用`x&31`能快速得到字母顺序。”  
  - **点评**：这个技巧能简化大小写判断的代码，但要注意`&31`的适用范围（只能用于字母）。  
- **作者Sinwind**：“统一转为大写计算，再恢复大小写，能避免复杂的条件判断。”  
  - **点评**：这是处理“大小写不敏感”问题的通用方法，比如密码验证、字符串比较都能用。  


## 结语
Vigenère密码的解密过程，本质是**“按规则一步步还原”**——就像解拼图，每一步都要按照说明书来，同时注意边界和细节。通过这道题，你学会的不仅是解密方法，更是“如何把复杂规则转化为代码”的能力。  

记住：编程的核心是“解决问题”，而不是“写复杂的代码”。像ingu那样用技巧简化代码，像Sinwind那样用函数理清思路，像3_14那样拆分问题，你就能慢慢成为“会解决问题的程序员”！  

下次我们再一起探索更有趣的算法题，加油！💪

---
处理用时：104.78秒