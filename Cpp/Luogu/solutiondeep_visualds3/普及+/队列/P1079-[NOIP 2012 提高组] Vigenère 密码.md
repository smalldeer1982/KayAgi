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

# 💡 Kay的C++算法解析：[NOIP 2012 提高组] Vigenère 密码 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串处理 + 模运算应用`  

🗣️ **初步分析**：  
解决“Vigenère 密码”问题，本质是**字符的“逆翻译”游戏**——用密钥作为“翻译字典”，将密文转换回明文。就像你有一本密码本，每个密文字符需要用密钥中的对应字符“查字典”，才能得到原来的意思。而密钥会循环使用（比如密钥是“abc”，密文第4个字符会再次用“a”翻译）。  

**核心思路**：  
1. 对每个密文字符，找到对应的密钥字符（忽略密钥大小写）；  
2. 计算密钥字符的“偏移量”（比如“a”对应偏移0，“b”对应偏移1，依此类推）；  
3. 将密文字符减去偏移量（逆加密过程），如果结果小于字母表起始位置（如'A'或'a'），就加26绕回（比如'A'-1变成'Z'）；  
4. 保持密文的大小写不变（比如密文是大写，明文也大写）。  

**核心难点**：  
- 大小写处理（密钥忽略大小写，密文保持大小写）；  
- 密钥循环（密文比密钥长时，重复使用密钥）；  
- 边界处理（减偏移后可能越界，需要加26调整）。  

**可视化设计思路**：  
用8位像素风格模拟“密码破译机”，屏幕分为**密钥区**（循环部分高亮）、**密文区**（当前处理字符红色闪烁）、**明文区**（逐步生成）、**计算区**（显示偏移量、差值等中间结果）。每处理一步播放“叮”的音效，完成后播放“胜利”旋律，让你直观看到“字符如何一步步变明文”。


## 2. 精选优质题解参考

为大家筛选了**思路清晰、代码简洁、实用性强**的3道题解，评分均≥4星：


### **题解一：作者：ingu（赞：472）**  
* **点评**：  
  这道题解的**最大亮点是代码极短（仅10行）**，却完美解决了所有问题！作者用了一个巧妙的技巧：`&31`（二进制11111），可以提取字母的后5位（比如'A'的ASCII是65，&31后是1；'a'是97，&31后也是1），**直接忽略大小写**。然后计算偏移量`t=(密钥字符&31)-1`（因为加密是加偏移，解密是减），再调整密文字符：如果`密文&31 - t`>0，直接减；否则加26。代码逻辑简洁到“一句话解决问题”，非常适合学习**如何用技巧简化代码**。


### **题解二：作者：Sinwind（赞：3）**  
* **点评**：  
  这道题解的**优势是逻辑清晰、可读性高**。作者将解密过程封装成`decryption`函数，输入密文字符和密钥字符，输出明文字符。函数内先将两者转为大写（统一处理），计算差值（如果密文大写≥密钥大写，直接减；否则加26再减），再根据密文的大小写转换回对应的字符（大写用'A'加，小写用'a'加）。这种**函数封装**的方式非常适合初学者，能清晰看到“每一步做了什么”。


### **题解三：作者：ShirasuAzusaSaikou（赞：2）**  
* **点评**：  
  这道题解的**亮点是处理密钥的方式**：先将密钥转为小写（`tolower`），然后循环处理密文字符时，将密文也转为小写计算差值，最后根据密文原来的大小写转换回字符。这种**统一密钥大小写**的方法，避免了多次判断密钥的大小写，代码更简洁。循环密钥用`ki=(ki+1)%kl`（kl是密钥长度），逻辑清晰，容易理解。


## 3. 核心难点辨析与解题策略

### **1. 难点1：大小写处理**  
**问题**：密钥忽略大小写，密文要保持原来的大小写。  
**解决策略**：  
- 密钥：用`&31`、`tolower`或`toupper`统一处理（比如`密钥字符&31`可以忽略大小写，得到1-26的字母顺序）；  
- 密文：记录其大小写（比如`密文[i] >= 'a'`表示小写），计算后再转回去（比如小写用'a'加，大写用'A'加）。  

💡 **学习笔记**：大小写处理的关键是“统一计算，保留结果”。


### **2. 难点2：循环密钥**  
**问题**：密文长度可能大于密钥长度，需要重复使用密钥。  
**解决策略**：  
用`i%key.length()`获取当前密钥字符的索引（`i`是密文的第`i`个字符）。比如密钥长度是3，密文第4个字符对应密钥第`4%3=1`个字符（索引从0开始的话是第0个？不，`i%key.length()`的结果是0到key.length()-1，正好对应密钥的每个字符）。  

💡 **学习笔记**：循环问题用“模运算”解决，这是编程中的常用技巧。


### **3. 难点3：边界处理**  
**问题**：密文字符减偏移量后可能小于'A'或'a'（比如'A'-1）。  
**解决策略**：  
计算时加26再取模，确保结果非负。比如`(密文顺序 - 偏移量 + 26) %26`（密文顺序是1-26，偏移量是0-25），这样即使密文顺序-偏移量是负数，加26后也会变成正数，再取模就不会越界。  

💡 **学习笔记**：模运算可以解决“绕圈”问题，比如钟表的12点减1是11点，就是`(12-1)%12=11`。


### ✨ 解题技巧总结  
- **技巧1**：用`&31`提取字母顺序（忽略大小写），简化代码；  
- **技巧2**：循环密钥用`i%key.length()`，避免手动循环；  
- **技巧3**：边界处理用`(x + 26) %26`，确保结果非负；  
- **技巧4**：函数封装（如Sinwind的`decryption`函数），提高代码可读性。


## 4. C++核心代码实现赏析

### **本题通用核心C++实现参考**  
* **说明**：综合了ingu和Sinwind的思路，兼顾简洁性和可读性。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <string>
  using namespace std;

  int main() {
      string key, cipher;
      cin >> key >> cipher;
      int kl = key.size();
      for (int i = 0; i < cipher.size(); ++i) {
          // 提取密钥字符的偏移量（忽略大小写）
          int offset = (key[i % kl] & 31) - 1; // 比如'A'&31=1，偏移量是0
          // 提取密文字符的字母顺序（忽略大小写）
          int cipher_order = cipher[i] & 31;
          // 计算明文字符的字母顺序（减偏移，加26取模）
          int plain_order = (cipher_order - offset + 26) % 26;
          // 转换回字符，保持原来的大小写
          if (cipher[i] >= 'a') {
              cipher[i] = 'a' + plain_order - 1; // 1-26→0-25
          } else {
              cipher[i] = 'A' + plain_order - 1;
          }
      }
      cout << cipher << endl;
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. 读取密钥和密文；  
  2. 循环处理每个密文字符：  
     - 用`&31`提取密钥和密文的字母顺序（1-26）；  
     - 计算偏移量（密钥顺序-1）；  
     - 计算明文字母顺序（密文顺序-偏移量+26取模）；  
     - 根据密文的大小写，将明文字母顺序转换回字符（1-26→0-25，加'A'或'a'）；  
  3. 输出解密后的明文。


### **针对各优质题解的片段赏析**

#### **题解一（作者：ingu）**  
* **亮点**：用`&31`忽略大小写，代码极短。  
* **核心代码片段**：  
  ```cpp
  int t = (k[i % k.length()] & 31) - 1;
  c[i] = (c[i] & 31) - t > 0 ? c[i] - t : c[i] - t + 26;
  ```  
* **代码解读**：  
  - `k[i % k.length()] & 31`：提取密钥字符的字母顺序（1-26）；  
  - `t`：偏移量（密钥顺序-1）；  
  - `c[i] & 31`：提取密文字符的字母顺序（1-26）；  
  - 三元运算符：如果`密文顺序 - t`>0，直接减`t`（比如'A'-0='A'）；否则加26（比如'A'-1→'Z'）。  
* 💡 **学习笔记**：`&31`是处理字母大小写的“神器”，能快速提取字母顺序。


#### **题解二（作者：Sinwind）**  
* **亮点**：函数封装，逻辑清晰。  
* **核心代码片段**：  
  ```cpp
  char decryption(char c, char k) {
      char temp_c = toupper(c);
      char temp_k = toupper(k);
      char m = (isupper(c)) ? 'A' : 'a';
      m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);
      return m;
  }
  ```  
* **代码解读**：  
  - `toupper(c)`和`toupper(k)`：将密文和密钥转为大写，统一处理；  
  - `isupper(c)`：判断密文是否为大写，决定明文字符的起始（'A'或'a'）；  
  - 三元运算符：如果密文大写≥密钥大写，直接减；否则加26再减（避免负数）。  
* 💡 **学习笔记**：函数封装能让代码更清晰，适合初学者理解“每一步的作用”。


#### **题解三（作者：ShirasuAzusaSaikou）**  
* **亮点**：统一密钥大小写，代码简洁。  
* **核心代码片段**：  
  ```cpp
  for (auto &i : k) i = tolower(i); // 将密钥转为小写
  for (int i = 0; i < ml; i++) {
      cout << (char)(((m[i] >= 'a') ? 'a' : 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
      ki = (ki + 1) % kl; // 循环密钥
  }
  ```  
* **代码解读**：  
  - `tolower(i)`：将密钥转为小写，避免多次判断；  
  - `tolower(m[i])`：将密文转为小写，计算差值；  
  - `(tolower(m[i]) - k[ki] + 26) % 26`：计算明文字母顺序（0-25）；  
  - `(m[i] >= 'a') ? 'a' : 'A'`：根据密文的大小写，转换回字符。  
* 💡 **学习笔记**：统一密钥大小写能简化代码，减少判断次数。


## 5. 算法可视化：像素动画演示 (核心部分)

### **动画演示主题**：像素密码破译机（FC风格）  

### **设计思路**  
用8位像素风格模拟“密码破译”过程，结合**游戏化元素**（音效、积分、关卡），让你在“玩”中理解算法。比如：  
- 密钥区：显示密钥字符串，当前使用的字符用**黄色高亮**，循环时闪烁；  
- 密文区：显示密文字符串，当前处理的字符用**红色闪烁**；  
- 明文区：逐步显示解密后的明文字符，每处理一个字符就添加一个；  
- 计算区：显示当前的**偏移量**（密钥字符&31-1）、**密文顺序**（密文字符&31）、**明文顺序**（计算后的值）。  

### **动画帧步骤**  
1. **初始化**：  
   - 屏幕显示“像素密码破译机”标题（8位字体）；  
   - 密钥区显示输入的密钥（比如“abc”）；  
   - 密文区显示输入的密文（比如“Bcd”）；  
   - 明文区为空，计算区显示“准备就绪”；  
   - 播放8位风格的背景音乐（比如《超级马里奥》的开场音乐）。  

2. **单步执行**（点击“单步”按钮）：  
   - 密钥区当前字符（比如“a”）用**黄色高亮**，并显示“当前密钥：a”；  
   - 密文区当前字符（比如“B”）用**红色高亮**，并显示“当前密文：B”；  
   - 计算区显示：“偏移量：0”（a&31=1→1-1=0）、“密文顺序：2”（B&31=2）、“明文顺序：2”（2-0=2→2+26=28？不，2-0=2，加26取模还是2）；  
   - 明文区添加“B”（因为密文是大写，所以用'A'+2-1='B'）；  
   - 播放“叮”的音效（8位风格）。  

3. **自动播放**（点击“自动”按钮）：  
   - 按照设定的速度（比如每秒1步）自动处理所有字符；  
   - 每处理一个字符，上述步骤自动执行；  
   - 完成后，明文区显示完整的明文（比如“Abc”），播放“胜利”音效（比如《超级马里奥》的通关音乐），并显示“破译成功！得分：100”。  

4. **重置**（点击“重置”按钮）：  
   - 恢复初始状态，等待输入新的密钥和密文。  

### **游戏化元素**  
- **积分系统**：每处理一个字符得10分，完成所有字符得100分；  
- **关卡设计**：分为“简单”（密钥长度=密文长度）、“中等”（密钥长度<密文长度）、“困难”（密钥长度远<密文长度）三个关卡；  
- **音效**：处理字符时播放“叮”，完成时播放“胜利”，错误时播放“警告”（比如输入非字母字符）。  


## 6. 拓展练习与相似问题思考

### **通用思路/技巧迁移**  
本题的**字符串处理**、**循环密钥**、**模运算**技巧，适用于以下场景：  
1. **凯撒密码解密**：密钥是固定的偏移量（比如偏移3），用类似的模运算解决；  
2. **简单替换密码**：将每个字符替换为另一个字符（比如'a'→'d'，'b'→'e'），用字符映射表解决；  
3. **字符串加密**：比如将字符串转换为“大写+偏移”的格式，用类似的逻辑处理。  


### **练习推荐 (洛谷)**  
1. **洛谷 P1032 字串变换**：  
   - 🗣️ **推荐理由**：锻炼字符串替换和循环处理能力，类似“密码转换”的思路。  
2. **洛谷 P1125 笨小猴**：  
   - 🗣️ **推荐理由**：统计字符串中字符出现的次数，锻炼字符串遍历和计数能力。  
3. **洛谷 P2081 密码**：  
   - 🗣️ **推荐理由**：简单密码解密问题，类似Vigenère密码，锻炼模运算应用能力。  
4. **洛谷 P3954 成绩**：  
   - 🗣️ **推荐理由**：虽然不是字符串问题，但涉及模运算（计算平均分），锻炼模运算的应用能力。  


## 7. 学习心得与经验分享 (若有)

### **参考经验 (来自 ingu)**  
> “我用了&31的技巧，因为字母的ASCII码后5位是相同的，这样可以忽略大小写。比如'A'是65（01000001），'a'是97（01100001），&31后都是1，这样处理起来很方便。”  

**点评**：  
这个技巧非常实用！`&31`能快速提取字母的顺序，避免了多次判断大小写的麻烦。初学者可以记住这个技巧，处理字母问题时会很有用。


### **参考经验 (来自 Sinwind)**  
> “我将解密过程封装成了函数，这样代码更清晰，也容易调试。比如如果函数有问题，只需要检查函数内部，不需要看整个main函数。”  

**点评**：  
函数封装是编程中的重要技巧，能提高代码的可读性和可维护性。初学者应该学会将复杂的逻辑封装成函数，这样代码会更有条理。


## 🎉 结语  
本次关于“Vigenère 密码”的分析就到这里啦！希望这份指南能帮助你理解**字符串处理**和**模运算**的应用，掌握解题的核心技巧。记住：**编程的关键是“思路清晰”，技巧是为思路服务的**。下次遇到类似问题，不妨试试今天学的技巧，相信你会做得更好！💪  

如果有任何问题，欢迎在评论区留言，Kay会尽力帮助你！😊

---
处理用时：338.79秒