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

# 💡 Kay的C++算法解析：[NOIP 2012 提高组] Vigenère 密码 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串模拟`（侧重字符处理与规则还原）


🗣️ **初步分析**：  
解决“Vigenère 密码”的核心是**模拟解密规则**——就像“每个密文字符根据密钥的指示，从字母表中往回走几步，注意不要走出边界（A→Z或a→z）”。具体来说，我们需要：  
1. 对每个密文字符，找到对应的密钥字符（密钥循环使用）；  
2. 计算密文字符相对于密钥字符的“回退步数”（即偏移量）；  
3. 保持明文的大小写与密文一致（密钥忽略大小写）。  

**核心算法流程**：  
- 遍历密文`c`的每个字符`c[i]`；  
- 取密钥`k`的第`i%k.length()`个字符`k[j]`（循环使用）；  
- 将`c[i]`和`k[j]`转换为字母顺序（如A→0，a→0）；  
- 计算明文顺序：`(c顺序 - k顺序 + 26) % 26`（加26避免负数）；  
- 将明文顺序转换为字符（保持密文的大小写）。  

**可视化设计思路**：  
用8位像素风格展示密文、密钥和明文的动态变化：  
- 密文字符用**红色像素块**标记，密钥字符用**蓝色像素块**标记；  
- 计算偏移时，显示**数字动画**（如“-3”），并伴随“叮”的音效；  
- 明文结果用**绿色像素块**显示，完成时播放“胜利”音效。  
- 支持“单步执行”（逐字符解密）和“自动播放”（快速演示），让你直观看到每个字符的变化过程。


## 2. 精选优质题解参考

为了帮你快速掌握解题技巧，我从思路清晰度、代码效率、启发性三个方面筛选了以下3份优质题解：


### **题解一：（作者：ingu，赞：480）**  
* **点评**：这份题解的代码**极其简洁**（仅10行），却完美覆盖了所有规则！作者用`&31`（二进制`11111`）的技巧，巧妙地将大写字母（如'A'→65）和小写字母（如'a'→97）统一转换为字母顺序（如'A'&31=1，'a'&31=1），避免了繁琐的`tolower`/`toupper`判断。偏移计算`c[i]-t`（`t`是密钥顺序-1）的处理也很聪明——如果结果为负，就加26，确保不会越界。这种“用位运算简化大小写处理”的技巧，值得你反复琢磨！


### **题解二：（作者：huluobotou，赞：40）**  
* **点评**：这份题解的思路**非常独特**！作者观察到密码表中“斜行的字母加和相同”（如A+A=2，B+B=4，Z+Z=52），于是预先计算了每个字母的“加和值”，通过“密文加和 - 密钥顺序”反推明文顺序。虽然代码较长，但这种“从表格规律入手”的思考方式，能帮你更深刻地理解密码表的本质。另外，作者用`v`数组记录密文的大小写，确保明文与密文一致，这种“记录状态”的方法也很实用。


### **题解三：（作者：LightCoder，赞：33）**  
* **点评**：这份题解的**可视化思路**很值得学习！作者用`queue`（队列）模拟密码表的生成——就像“把字母排成一队，每次把队头放到队尾，生成下一行”。这种方法把抽象的密码表变成了具体的队列操作，非常直观。虽然代码中打表的部分有点长，但“用数据结构模拟规律”的思维，能帮你解决更多类似的“表格类”问题（如凯撒密码、移位密码）。


## 3. 核心难点辨析与解题策略

在解密过程中，你可能会遇到以下3个核心难点，结合优质题解的做法，我帮你总结了应对策略：


### **1. 难点1：如何处理大小写？**  
**问题**：密文的大小写要保持到明文，而密钥的大小写不影响结果。  
**解决策略**：  
- 用`&31`（或`tolower`/`toupper`）统一密钥的大小写（如`k[j]&31`将'A'和'a'都转换为1）；  
- 记录密文的大小写（如用`v[i]`标记`c[i]`是否为大写），解密后根据记录恢复明文的大小写。  
**例子**：ingu的题解中，`c[i]&31`获取密文的顺序，`k[j]&31`获取密钥的顺序，最后用`c[i]`的原始值减去偏移量（保持大小写）。


### **2. 难点2：如何循环使用密钥？**  
**问题**：当密文长度大于密钥长度时，需要重复使用密钥。  
**解决策略**：用`i%k.length()`获取当前密钥字符的索引（`i`是密文的当前位置）。  
**例子**：所有题解中都用到了这个技巧，比如ingu的`k[i%k.length()]`，huluobotou的`i%l2`（`l2`是密钥长度）。


### **3. 难点3：如何计算偏移量（避免负数）？**  
**问题**：当密文顺序小于密钥顺序时（如密文是'A'，密钥是'B'），直接减会得到负数（0-1=-1），需要调整到字母表的末尾（如'Z'）。  
**解决策略**：用`(密文顺序 - 密钥顺序 + 26) % 26`计算明文顺序（加26确保结果非负，取模26回到字母表范围）。  
**例子**：3_14的题解中，`(cNum - kNum + 26) % 26`就是典型的处理方式。


### ✨ 解题技巧总结  
- **位运算简化大小写**：用`&31`或`^32`（如`c ^= 32`将大写转小写），比`tolower`更高效；  
- **记录状态**：如果需要保持某些属性（如大小写），提前用数组或变量记录；  
- **模运算循环**：处理“重复使用”的问题时，模运算（`%`）是神器。


## 4. C++核心代码实现赏析


### **本题通用核心C++实现参考**  
* **说明**：综合了ingu的简洁思路和3_14的清晰结构，适合快速理解核心逻辑。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <string>
  using namespace std;

  int main() {
      string key, cipher;
      cin >> key >> cipher;
      int key_len = key.size();
      for (int i = 0; i < cipher.size(); ++i) {
          // 取当前密钥字符（循环使用）
          char k_char = key[i % key_len];
          // 转换为字母顺序（A/a→1，B/b→2，…，Z/z→26）
          int k_order = (k_char & 31) - 1; // 减1是为了让A→0，方便计算
          // 计算明文顺序：(密文顺序 - 密钥顺序 + 26) % 26
          int c_order = (cipher[i] & 31) - 1;
          int m_order = (c_order - k_order + 26) % 26;
          // 恢复明文的大小写（与密文一致）
          if (cipher[i] >= 'a') {
              cipher[i] = 'a' + m_order;
          } else {
              cipher[i] = 'A' + m_order;
          }
      }
      cout << cipher << endl;
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. 读取密钥和密文；  
  2. 遍历密文的每个字符，取对应的密钥字符；  
  3. 将密钥和密文转换为字母顺序（`&31`统一大小写）；  
  4. 计算明文顺序（避免负数）；  
  5. 恢复明文的大小写（与密文一致）；  
  6. 输出明文。


### **针对各优质题解的片段赏析**


#### **题解一（作者：ingu）**  
* **亮点**：用`&31`简化大小写处理，代码极致简洁。  
* **核心代码片段**：  
  ```cpp
  for (int i=0;i<c.length();i++) {
      int t=(k[i%k.length()]&31)-1;
      c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
  }
  ```  
* **代码解读**：  
  - `k[i%k.length()]&31`：将密钥字符转换为字母顺序（如'A'→1，'a'→1）；  
  - `t`是密钥顺序减1（如'A'→0，'B'→1）；  
  - `c[i]&31`：将密文转换为字母顺序；  
  - `(c[i]&31)-t`：计算明文顺序（未加26）；  
  - 三元运算符：如果结果>0，直接减`t`；否则加26（避免负数）。  
* 💡 **学习笔记**：`&31`是处理字母大小写的“神技巧”，记住它能帮你节省很多代码！


#### **题解二（作者：huluobotou）**  
* **亮点**：用斜行加和的方法反推明文，思路独特。  
* **核心代码片段**：  
  ```cpp
  // 预先计算每个字母的加和值（斜行）
  for(int i=1;i<=26;i++)  
      x[i]=i+1,x[26+i]=i+1+26;
  // 计算明文顺序
  if(x[a1[i]]>b1[n])
      c1[i]=x[a1[i]]-b1[n];
  else
      c1[i]=x[a1[i]+26]-b1[n];
  ```  
* **代码解读**：  
  - `x`数组存储每个字母的“加和值”（如'A'→2，'B'→3，…，'Z'→27，再循环）；  
  - `a1[i]`是密文的顺序（如'A'→1，'B'→2）；  
  - `b1[n]`是密钥的顺序；  
  - 用“密文加和 - 密钥顺序”得到明文顺序（如果加和小于密钥顺序，就用下一个循环的加和）。  
* 💡 **学习笔记**：观察表格规律能帮你找到更高效的解法，比如“斜行加和”就是从密码表中发现的。


#### **题解三（作者：LightCoder）**  
* **亮点**：用队列模拟密码表的生成，直观易懂。  
* **核心代码片段**：  
  ```cpp
  // 初始化队列（A→1，B→2，…，Z→26）
  for(int i=1;i<=26;i++) q.push(i);
  // 生成密码表
  for(int i=1;i<=26;i++){
      Mid=q.front();
      q.push(Mid);q.pop(); // 队头放到队尾，生成下一行
      for(register int j=26;j>=1;j--){
          Mid=q.front();
          Map[i][j]=q.front(); // 填充当前行的密码表
          q.push(Mid);q.pop();
      }
  }
  ```  
* **代码解读**：  
  - `q`队列存储当前行的字母顺序；  
  - 每次生成下一行时，将队头放到队尾（模拟密码表的“移位”）；  
  - 填充`Map`数组（密码表），其中`Map[i][j]`表示密钥为第`i`个字母、明文为第`j`个字母时的密文顺序。  
* 💡 **学习笔记**：用数据结构（如队列）模拟规律，能让抽象的问题变得具体，容易理解。


## 5. 算法可视化：像素动画演示（核心部分）


### **动画演示主题**：`像素解密师`（仿FC游戏风格）


### **核心演示内容**：  
展示密文`Yvqgpxaimmklongnzfwpvxmniytm`和密钥`CompleteVictory`的解密过程，每一步都能看到：  
1. 当前处理的**密文字符**（红色像素块）；  
2. 对应的**密钥字符**（蓝色像素块）；  
3. 偏移计算（如“-3”的数字动画）；  
4. 生成的**明文字符**（绿色像素块）。


### **设计思路简述**：  
- **8位像素风格**：用红白机的配色（红、蓝、绿、黑），让动画更有复古感；  
- **音效增强记忆**：每个字符处理时播放“叮”的音效（表示计算完成），全部解密完成时播放“胜利”音效（如《超级马里奥》的通关音乐）；  
- **交互控制**：支持“单步执行”（逐字符解密）、“自动播放”（快速演示）和“重置”（重新开始），让你可以反复观察；  
- **游戏化元素**：将解密过程设计为“关卡”，每解密5个字符就显示“过关”提示，增加成就感。


### **动画帧步骤**：  
1. **初始化**：屏幕左侧显示密文字符（红色），右侧显示密钥字符（蓝色），中间显示“准备解密”的提示；  
2. **单步执行**：点击“下一步”，当前密文字符（如第一个字符`Y`）变红，对应的密钥字符（`C`）变蓝；  
3. **计算偏移**：中间显示“Y（24） - C（2） = 22”（`Y`的顺序是24，`C`的顺序是2），然后显示“22 + 26 = 48 → 48 % 26 = 22”（避免负数）；  
4. **生成明文**：明文字符`W`（22对应的大写字母）变绿，显示在密文字符下方；  
5. **循环处理**：重复步骤2-4，直到所有字符解密完成；  
6. **胜利提示**：屏幕显示“解密成功！”，播放胜利音效，明文字符全部变绿。


### **技术实现要点**：  
- **Canvas绘制**：用`ctx.fillRect`绘制像素块（每个字符占10x10像素）；  
- **音效**：用`Audio`对象播放8位音效（如`ding.mp3`、`win.mp3`）；  
- **交互**：用`addEventListener`处理按钮点击（如“下一步”、“自动播放”）。


## 6. 拓展练习与相似问题思考


### **通用思路/技巧迁移**：  
本题的“字符偏移”和“循环使用密钥”技巧，可用于解决以下问题：  
1. **凯撒密码**（固定偏移量，如所有字符加3）；  
2. **移位密码**（如每个字符根据前一个字符的偏移量变化）；  
3. **字符串加密/解密**（如替换密码、维吉尼亚密码的变种）。


### **练习推荐（洛谷）**：  
1. **洛谷 P1088** - [火星人](https://www.luogu.com.cn/problem/P1088)  
   🗣️ **推荐理由**：这道题需要处理字符串的“下一个排列”，涉及字符的移位和循环，能帮你巩固“字符处理”的技巧。  
2. **洛谷 P1125** - [笨小猴](https://www.luogu.com.cn/problem/P1125)  
   🗣️ **推荐理由**：这道题需要统计字符串中字母的出现次数，涉及字符的遍历和计数，能帮你熟悉“字符串遍历”的方法。  
3. **洛谷 P1200** - [USACO1.1]你的飞碟在这儿Your Ride Is Here  
   🗣️ **推荐理由**：这道题需要将字符串转换为数字并计算乘积，涉及字符到数字的转换，能帮你巩固“字符编码”的知识。


## 7. 学习心得与经验分享（若有）


### **参考经验（来自题解作者：ingu）**：  
“我在解决这道题时，一开始用了`tolower`函数处理大小写，但后来发现`&31`更高效，因为位运算比函数调用更快。这让我意识到，了解ASCII码的二进制结构，能帮你找到更简洁的解法。”  

**点评**：这位作者的经验很实用！在编程中，位运算往往比函数调用更高效，尤其是处理字符大小写时，`&31`或`^32`是很好的选择。比如，`c ^= 32`可以快速将大写字母转为小写，小写转为大写（因为大写字母的ASCII码二进制第6位是0，小写是1，`^32`就是翻转第6位）。


## 结语  
本次关于“Vigenère 密码”的分析就到这里啦！希望这份指南能帮你掌握字符串模拟的核心技巧，学会处理大小写、循环使用密钥和偏移计算。记住，编程的乐趣在于“解决问题”，而不是“写复杂的代码”——像ingu那样用简洁的代码解决问题，才是高手的境界！  

下次我们再一起探索新的编程挑战，加油！💪

---
处理用时：235.45秒