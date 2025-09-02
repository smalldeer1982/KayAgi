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



---
# 💡 Kay的C++算法解析：Vigenère密码 深入学习指南 💡

<introduction>
今天我们要一起攻克的是NOIP2012提高组的“Vigenère密码”解密问题。这道题看似涉及密码学，但核心是字符串处理和模运算的应用。通过这份指南，你将学会如何逆向破解Vigenère密码，掌握关键的编程技巧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`编程技巧应用（字符串处理+模运算）`

🗣️ **初步分析**：
Vigenère密码的加密规则是“用密钥字符对明文字符进行循环移位”，而解密则是其逆过程。简单来说，加密像“明文字母A被密钥B移位后变成B”，解密就是“密文字母B被密钥B移位后变回A”。这里的“移位”需要循环处理（比如Z移位后回到A），所以核心是用模运算解决循环问题。

- **题解思路**：所有优质题解的核心思路高度一致：将密钥和密文字符转换为0-25的数值（A/a=0，B/b=1...Z/z=25），利用公式`明文数值 = (密文数值 - 密钥数值 + 26) % 26`计算明文数值，再转换回字符。难点在于处理密钥的循环使用（密钥长度不足时重复）和保持明文的大小写与密文一致。
  
- **可视化设计**：我们将设计一个“复古密码本”像素动画，用8位风格的格子表示字母表，每一步解密时高亮当前密文字符、对应的密钥字符，用箭头展示数值计算过程（如密文数值-密钥数值=明文数值），并通过颜色变化（红→绿）表示解密成功。关键步骤会有“叮”的音效提示，完成所有解密后播放“胜利”音效。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下题解因逻辑简洁、实现高效被选为优质参考：
</eval_intro>

**题解一：作者@ingu（赞472）**
* **点评**：此题解代码极其简洁，巧妙利用位运算`&31`将字符统一转换为0-25的数值（因为'A'和'a'的ASCII码后5位相同），避免了复杂的大小写判断。代码仅用10行完成核心逻辑，边界处理（如减法后负数）通过条件判断简化，非常适合竞赛场景。

**题解二：作者@Sinwind（赞3）**
* **点评**：此题解结构清晰，将解密过程封装为`decryption`函数，明确分离了“字符转换”和“数值计算”逻辑。函数参数和变量命名直观（如`temp_c`表示统一后的密文字符），注释详细，适合初学者理解每一步操作。

**题解三：作者@ShirasuAzusaSaikou（赞1）**
* **点评**：此题解代码简洁且兼顾效率，使用`tolower`统一处理密钥的大小写，避免了重复判断。核心计算通过`(tolower(m[i]) - k[ki] + 26) % 26`直接完成，代码可读性强，适合快速实现。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题时，我们可能遇到以下核心难点，结合优质题解的思路，我们逐一分析：
</difficulty_intro>

1.  **关键点1：字符到数值的转换（处理大小写）**
    * **分析**：密文和密钥可能包含大小写字母，但加密时忽略大小写。例如，密钥'A'和'a'效果相同。优质题解通常将字符统一转换为大写或小写（如`tolower`函数），或通过`c - 'A'`（大写）、`c - 'a'`（小写）转换为0-25的数值。
    * 💡 **学习笔记**：统一处理大小写是简化问题的关键，可用`tolower`或位运算（如`c & 31`）快速转换。

2.  **关键点2：密钥的循环使用**
    * **分析**：当密文长度大于密钥长度时，密钥需要重复使用。优质题解通过`i % key_len`（`i`是密文当前索引，`key_len`是密钥长度）实现循环，例如`key[i % key_len]`直接取当前对应的密钥字符。
    * 💡 **学习笔记**：模运算（%）是处理循环问题的“万能钥匙”，记住`i % n`的取值范围是0~n-1。

3.  **关键点3：模运算的正确应用（避免负数）**
    * **分析**：计算`明文数值 = 密文数值 - 密钥数值`时可能得到负数（如密文是A=0，密钥是B=1，0-1=-1），需要加26后取模。优质题解用`(c_num - k_num + 26) % 26`确保结果非负。
    * 💡 **学习笔记**：减法后加26再取模，能保证结果在0-25之间，避免循环越界。

### ✨ 解题技巧总结
- **统一大小写**：将密钥和密文字符统一转换为大写或小写，简化数值计算（如`k[i] = tolower(k[i])`）。
- **模运算循环密钥**：用`i % key_len`快速定位当前密钥字符，无需显式重复密钥字符串。
- **公式简化**：直接使用`(c_num - k_num + 26) % 26`计算明文数值，一步解决负数问题。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼出一个简洁且完整的核心实现，帮助你快速掌握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：此代码综合了@ingu和@Sinwind的思路，统一处理大小写，用模运算循环密钥，代码简洁且鲁棒性强。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    #include <cctype> // 用于tolower函数

    using namespace std;

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        int key_len = key.size();
        
        // 预处理密钥为小写（统一处理大小写）
        for (char &k : key) k = tolower(k);
        
        for (int i = 0; i < cipher.size(); ++i) {
            // 取当前密钥字符（循环使用）
            char k_char = key[i % key_len];
            // 密文字符的数值（0-25）
            int c_num = tolower(cipher[i]) - 'a';
            // 密钥字符的数值（0-25）
            int k_num = k_char - 'a';
            // 计算明文数值（避免负数）
            int m_num = (c_num - k_num + 26) % 26;
            
            // 保持明文的大小写与密文一致
            if (isupper(cipher[i])) {
                cout << (char)(m_num + 'A');
            } else {
                cout << (char)(m_num + 'a');
            }
        }
        
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取密钥和密文，将密钥统一转为小写（简化后续计算）。然后遍历密文每个字符，通过`i % key_len`循环获取密钥字符，计算密文和密钥的数值，用`(c_num - k_num + 26) % 26`得到明文数值，最后根据密文的大小写输出明文。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者@ingu**
* **亮点**：用`c & 31`快速将字符转换为0-25的数值（利用'A'和'a'的ASCII码后5位相同），代码极短。
* **核心代码片段**：
    ```cpp
    int t = (k[i%k.length()] & 31) - 1;
    c[i] = (c[i] & 31) - t > 0 ? c[i] - t : c[i] - t + 26;
    ```
* **代码解读**：
    - `k[i%k.length()] & 31`：将密钥字符（无论大小写）转换为1-26的数值（如'A'→1，'a'→1），减1后得到0-25的数值（对应t）。
    - `c[i] & 31`：将密文字符转换为1-26的数值（如'A'→1，'a'→1），减去t后若结果>0，直接作为明文数值；否则加26（处理循环）。
    - 最后直接修改密文字符串`c`，输出结果。
* 💡 **学习笔记**：位运算`&31`是快速统一大小写的技巧（因为'A'=65=0b1000001，后5位是00001；'a'=97=0b1100001，后5位也是00001）。

**题解二：作者@Sinwind**
* **亮点**：封装`decryption`函数，逻辑清晰，明确分离“字符处理”和“数值计算”。
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
    - `toupper(c)`和`toupper(k)`：将字符统一转为大写，简化数值计算。
    - `m`的初始值设为'A'或'a'（根据密文的大小写），确保明文的大小写与密文一致。
    - 条件判断`temp_c >= temp_k`：若密文数值≥密钥数值，直接相减；否则加26再减（避免负数）。
* 💡 **学习笔记**：函数封装能提高代码的可读性和复用性，适合复杂逻辑的拆分。

**题解三：作者@ShirasuAzusaSaikou**
* **亮点**：代码简洁，用`tolower`统一处理密钥，避免重复判断。
* **核心代码片段**：
    ```cpp
    for(auto &i : k) i = tolower(i);
    for(int i = 0; i < ml; i++){
        cout <<(char) (((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
        ki = (ki + 1) % kl;
    }
    ```
* **代码解读**：
    - `for(auto &i : k) i = tolower(i)`：将密钥统一转为小写，后续无需再判断大小写。
    - `(tolower(m[i]) - k[ki] + 26) % 26`：计算明文数值（密文小写数值-密钥小写数值+26后取模）。
    - `((m[i] >= 'a')? 'a': 'A')`：根据密文的大小写选择基准字符（'a'或'A'），确保明文大小写一致。
* 💡 **学习笔记**：预处理输入（如统一大小写）能减少后续判断，简化代码逻辑。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地看到解密过程，我们设计一个“复古密码本”像素动画，用8位风格模拟Vigenère解密的每一步！
</visualization_intro>

  * **动画演示主题**：`像素密码本：Vigenère解密大冒险`

  * **核心演示内容**：展示密文字符、密钥字符的数值转换，以及`明文数值 = (密文数值 - 密钥数值 + 26) % 26`的计算过程，同时演示密钥的循环使用（如密钥长度3时，索引0→1→2→0→1...）。

  * **设计思路简述**：8位像素风格（类似FC游戏）能降低学习门槛，颜色高亮当前处理的字符和数值，音效（如“叮”）强化关键操作记忆，游戏化的“进度条”展示解密进度，增加成就感。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为三部分：左侧是“密文区”（黄色像素块，显示密文字符），中间是“密钥区”（蓝色像素块，显示密钥字符），右侧是“明文区”（绿色像素块，初始为空）。
          * 控制面板包含“单步”“自动播放”“重置”按钮和速度滑块（1-5倍速）。
          * 播放8位风格的轻快背景音乐（如《超级马里奥》经典旋律变奏）。

    2.  **密钥循环演示**：
          * 当密文长度超过密钥长度时，密钥区的字符循环显示（如密钥是"abc"，密文第4个字符对应密钥的第0个字符），用箭头动画（→）提示循环。

    3.  **字符转数值**：
          * 点击“单步”按钮，当前密文字符（如'Y'）和对应的密钥字符（如'v'）高亮（红色边框）。
          * 下方弹出“数值转换”窗口，显示字符→数值的过程（如'Y'→24，'v'→21），伴随“滴”的音效。

    4.  **数值计算**：
          * 计算明文数值：24（密文）-21（密钥）=3 → 3+26=29 → 29%26=3（避免负数）。
          * 用动态箭头（←）连接数值，显示计算过程，关键步骤（如加26、取模）用闪烁文字提示。

    5.  **明文生成**：
          * 明文区对应位置显示明文数值3对应的字符（'d'），颜色从灰变绿，伴随“叮”的音效。
          * 进度条前进一格（如总长度10，当前到第1格）。

    6.  **自动播放与完成**：
          * 点击“自动播放”，动画按设定速度连续执行，每步保留0.5秒的显示时间（可调速）。
          * 所有字符解密完成后，明文区整体闪烁，播放“胜利”音效（如《超级玛丽》吃金币音效），显示“解密成功！”文字。

  * **旁白提示**：
      - （单步时）“当前处理密文字符'Y'，对应密钥字符'v'。”
      - （数值转换时）“'Y'的数值是24（Y是第25个字母，从0开始计数），'v'的数值是21。”
      - （计算时）“24-21=3，结果非负，直接取3作为明文数值。”
      - （完成时）“明文是'd'，和密文的大小写一致！”

<visualization_conclusion>
通过这个动画，你可以直观看到每个字符的解密过程，理解密钥循环、数值转换和模运算的作用，就像在玩一个“密码破解小游戏”！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“循环移位+模运算”，这类思路在字符串处理中很常见。掌握后，你可以尝试解决以下问题：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - **凯撒密码**：固定移位的密码（如所有字符后移3位），是Vigenère的特例（密钥长度1）。
      - **栅栏密码**：将字符串按行拆分后重组，需要分析字符位置的循环规律。
      - **简单替换密码**：用固定映射表替换字符，需要统计字符频率破解（如英语中E出现频率最高）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1328 生活大爆炸版石头剪刀布** 
          * 🗣️ **推荐理由**：涉及循环规则（手势循环）和模运算，与Vigenère的密钥循环思路类似。
    2.  **洛谷 P1914 小书童——密码** 
          * 🗣️ **推荐理由**：基础的凯撒密码（固定移位），适合练习字符循环移位的处理。
    3.  **洛谷 P2039 [COCI2008-2009#2] 火车票** 
          * 🗣️ **推荐理由**：涉及字符串的循环截取和条件判断，能强化循环处理的技巧。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试时的经验，这些对我们很有启发：
</insights_intro>

> **参考经验 (来自@ShirasuAzusaSaikou)**：“一开始没处理负数的情况，比如密文是'A'（数值0），密钥是'B'（数值1），0-1=-1，直接转字符会出错。后来加了+26再取模，问题就解决了。”

**点评**：这个经验提醒我们，在处理模运算时，一定要考虑减法可能导致负数的情况。加上26后再取模是通用的解决方法，能确保结果在0-25之间。这一步看似简单，却是避免“越界”错误的关键！

-----

<conclusion>
Vigenère密码的解密问题，核心在于理解循环移位的逆运算，并通过模运算处理边界。通过今天的分析，你不仅学会了如何编写代码，还掌握了字符串处理、模运算和循环问题的解决技巧。接下来，快去尝试拓展练习，巩固你的技能吧！💪
</conclusion>

-----

---
处理用时：173.34秒