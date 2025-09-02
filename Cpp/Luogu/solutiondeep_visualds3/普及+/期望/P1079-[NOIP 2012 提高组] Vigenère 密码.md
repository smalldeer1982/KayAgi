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

> 今天我们来分析NOIP 2012提高组的Vigenère密码题目。本指南将帮助你理解这个经典密码算法的解密原理，掌握简洁高效的C++实现技巧，并通过有趣的像素动画直观理解解密过程。

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用`（字符串处理与数学变换）

🗣️ **初步分析**：
> Vigenère密码就像一场**字母旋转舞会**——每个密钥字符会带着密文字符旋转一定步数，我们要做的就是找到反方向旋转的步数。核心技巧是发现`(c_i - k_i + 26) % 26`的解密公式，就像把旋转过头的舞者拉回正确位置。
> - **题解核心思路**：所有优质解法都基于同一数学原理——将字母映射为0-25的数字后逆向计算位移
> - **三大难点**：1) 公式推导 2) 大小写处理 3) 密钥循环机制
> - **可视化设计**：将设计像素风字母转盘，用高亮箭头展示密钥字符"拉动"密文字符的逆向旋转过程，当字符越过'A'/'a'边界时触发8bit音效

---

## 2. 精选优质题解参考

**题解一（来源：ingu）**
* **点评**：此解法巧妙利用ASCII特性（`字符 & 31`获取字母序号），将解密公式浓缩为两行核心代码。其亮点在于用位运算替代传统大小写判断，使代码异常简洁（仅10行）。边界处理采用三目运算符实现"自动回环"，具有竞赛代码的典型高效性，但对初学者理解位运算稍有门槛。

**题解二（来源：qhr2023）**
* **点评**：采用模块化设计，单独编写`decryption`函数处理四种大小写组合情况。虽然代码稍长，但逻辑分区清晰，如同把解密过程拆解成四个独立车间。特别值得学习的是用`toupper`统一处理大小写的标准化思想，体现了良好的工程实践价值。

**题解三（来源：Sinwind）**
* **点评**：在代码简洁性（15行）与可读性间取得平衡，核心公式`(c-k+26)%26`如同密码解锁的关键齿轮。亮点在于用`(m[i] >= 'a' ? 'a' : 'A')`智能匹配大小写基址，避免冗余判断。其`ki`指针的循环控制堪称教科书级的取模应用示范。

---

## 3. 核心难点辨析与解题策略

1.  **公式推导的数学本质**
    * **分析**：观察加密表发现规律——明文字母序号 = (密文字母序号 - 密钥字母序号 + 26) mod 26。+26确保结果非负，%26处理字母表循环，如同旋转密码盘归位
    * 💡 学习笔记：将字母抽象为0-25数字是密码学常见技巧

2.  **大小写混合处理**
    * **分析**：优质题解均采用"统一计算，后期还原"策略。先转换为数字计算，再根据密文原始大小写决定输出格式。避免在计算过程中混杂大小写判断
    * 💡 学习笔记：`isupper()`和三元运算符`?:`是大小写处理的黄金搭档

3.  **密钥循环机制实现**
    * **分析**：通过`key_index = (key_index + 1) % key_length`实现密钥循环，如同让密钥指针在字符串末尾自动折返起点
    * 💡 学习笔记：循环缓冲区取模是处理周期性数据的通用技巧

### ✨ 解题技巧总结
- **数学建模法**：将字符操作转化为数值运算（ASCII码特性利用）
- **关注不变性**：加密/解密过程大小写不变，只需记录不需修改
- **防御性编程**：`+26`确保减法不出现负数，避免未定义行为
- **模块化设计**：独立函数处理解密单元（qhr2023方案）

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现参考**
```cpp
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    string key, cipher;
    cin >> key >> cipher;
    
    for (int i = 0; i < cipher.size(); ++i) {
        char k = key[i % key.size()];
        int offset = (tolower(k) - 'a') % 26;
        char base = islower(cipher[i]) ? 'a' : 'A';
        
        // 核心解密公式
        char plain = (cipher[i] - base - offset + 26) % 26 + base;
        cout << plain;
    }
    return 0;
}
```
* **代码解读概要**：
  - 第6-7行：读入密钥和密文
  - 第9行：通过取模实现密钥循环
  - 第10行：统一密钥字符为小写计算偏移量
  - 第11行：根据密文字符确定大小写基址
  - 第14行：核心数学变换，+26确保非负，%26处理回绕
  - 第15行：实时输出解密结果

---

**题解一（ingu）核心代码**
```cpp
int t=(k[i%k.length()]&31)-1;  // 魔法数字31提取字母序号
c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26; // 三目运算符处理边界
```
* **亮点**：利用位运算极简获取字母序号
* **代码解读**：
  > `k[...]&31`如同字母剥离器——无论大小写，都提取出1-26的序号（A=1）。解密时先判断直接减偏移量是否有效（结果>0），否则通过`+26`回绕到字母表末端。这种处理如同为字符安装"弹性边界"。
* 💡 学习笔记：位运算常用于字符特征提取，但需确保环境使用ASCII编码

**题解二（qhr2023）核心代码**
```cpp
char decryption(char c, char k) {
    if (k>='a' && c>='a') return (c-k+26)%26+'a';
    // 其他三种情况类似...
}
```
* **亮点**：严谨处理大小写组合的四种情况
* **代码解读**：
  > 将解密封装为函数，针对密钥/密文的大小写组合分情况处理。每种情况本质相同：统一基准计算偏移后还原大小写。如同为不同尺寸的密码锁定制适配器。
* 💡 学习笔记：函数封装提升代码复用性，特别适合多分支逻辑

**题解三（Sinwind）核心代码**
```cpp
char base = (cipher[i] >= 'a') ? 'a' : 'A';
char plain = (cipher[i] - base - offset + 26) % 26 + base;
```
* **亮点**：动态选择基准字符的优雅实现
* **代码解读**：
  > 通过三元运算符智能选择'a'或'A'作为计算基准，使核心公式统一处理大小写情况。%26确保结果在0-25范围内，最后加基准还原字符。这就像先用统一标尺测量，再放回正确位置。
* 💡 学习笔记：基准值动态选择是处理大小写混合的利器

---

## 5. 算法可视化：像素动画演示

### 复古密码破译机：8-bit风格解密模拟器

* **设计概念**：仿照80年代密码破译设备，用机械转盘可视化字符变换过程
* **核心交互**：
  ![Vigenère可视化示意图](https://example.com/vigenere-demo.gif)
  （图示：像素字符在转盘上被密钥"拉动"旋转）

* **动画流程**：
  1. **初始化**：16色像素屏幕显示两行文字：上方密文（黄色像素），下方密钥（蓝色像素）
  2. **指针联动**：
     - 红色像素块在密文下闪烁（当前处理位）
     - 蓝色像素块在密钥下同步移动（带齿轮转动音效）
  3. **字符变换演示**：
     - 左侧显示字母表环（26像素字符）
     - 绿色箭头从密钥字符指向字母表中心（表示偏移量）
     - 密文字符沿反方向旋转偏移量步数（每步触发"咔嗒"声）
     - 当旋转跨越'A'时触发清脆的"叮"声
  4. **结果输出**：解密字符以绿色像素浮现结果区

* **控制面板**：
  - [▶] 自动播放（调速滑块）
  - [→] 单步执行
  - [↺] 重置
  - [A] 切换大小写模式（像素文字变形动画）

* **游戏化元素**：
  - 每成功解密5个字符解锁一个成就徽章（像素贴纸）
  - 错误操作触发老式计算机"哔"错误音
  - 解密完成时播放8-bit胜利旋律

---

## 6. 拓展练习与相似问题思考

* **技能迁移**：本题训练的字符变换技巧还可应用于：
  1. 凯撒密码（单表替换密码）
  2. 字符串循环移位（如旋转数组）
  3. ASCII艺术生成（字符位置计算）

* **洛谷推荐**：
  1. [P1914 凯撒密码](https://www.luogu.com.cn/problem/P1914)  
     → 巩固基础字符变换
  2. [P1603 名字缩写](https://www.luogu.com.cn/problem/P1603)  
     → 训练大小写敏感处理
  3. [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)  
     → 进阶密码破译挑战

---

## 7. 学习心得与经验分享

> **参考经验**（来自题解调试注释）：
> "最初未处理密钥比密文短的情况，导致程序崩溃——这提醒我们边界测试的重要性"
> 
> **点评**：长度取模是循环结构的关键防御点，测试时应专门构造短密钥+长密文的边界用例。建议学习者在Dev-C++中开启地址边界检查（`-fsanitize=address`）快速定位越界错误。

---

本次Vigenère密码解析就到这里。记住：密码学本质是数学的艺术，而编程是将数学之美转化为实践的工具。下次遇到密码题时，不妨先画出变换示意图——让思维如解密动画般清晰可见！💪

---
处理用时：123.36秒