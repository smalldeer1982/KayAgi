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
今天我们来一起分析“Vigenère密码”这道经典的C++编程题。这道题涉及密码学中的多表加密解密，通过分析题解和代码，我们将掌握字符串处理、循环移位、模运算等核心技巧。让我们开始吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟与字符串处理（编程技巧应用）`

🗣️ **初步分析**：
> Vigenère密码的解密本质是“逆向循环移位”。简单来说，加密时每个明文字符会根据对应密钥字符的位置向后移位（例如密钥是'B'则移位1），解密时需要向前移位相同位数。例如，密文是'F'，密钥是'B'（移位1），则明文是'E'（'F'向前移1位）。若移位后超出字母范围（如'A'前移1位），则循环到'Z'。

   - **题解思路**：所有题解的核心都是“逆向移位”。具体步骤为：1）处理密钥的循环使用（密文长于密钥时，密钥重复）；2）统一处理大小写（加密/解密不区分密钥的大小写）；3）计算明文字符（密文字符 - 密钥移位量，若结果为负则+26）。
   - **核心难点**：如何正确处理循环移位（避免负数）、如何统一大小写计算、如何高效实现密钥的循环使用。
   - **可视化设计**：我们将设计一个“8位像素密码机”动画，用像素方块表示密文、密钥和明文。每一步演示当前处理的密文字符（高亮）、对应的密钥字符（循环显示），并通过箭头动画展示移位过程（如密文'F'←'E'←密钥'B'的移位1）。关键步骤伴随“叮”的音效，循环移位时用旋转动画表示字母循环。

---

## 2. 精选优质题解参考

<eval_intro>
经过对题解的思路清晰度、代码规范性、算法有效性等维度评估，以下题解因逻辑简洁、代码高效且易于学习，被选为优质题解（≥4星）：
</eval_intro>

**题解一：作者 - ingu (赞：472)**
* **点评**：此题解用位运算（&31）巧妙统一处理大小写，代码极短但逻辑清晰。例如，`k[i%k.length()]&31`将密钥字符转为1-26的数字（A-Z和a-z的后5位相同），`c[i]&31`同理处理密文字符。通过判断`(c[i]&31)-t>0`决定是否+26，一步完成循环移位。代码简洁到仅需10行，适合竞赛快速实现，边界处理（如循环移位）非常严谨。

**题解二：作者 - Sinwind (赞：3)**
* **点评**：此题解将解密过程封装为`decryption`函数，结构清晰。函数中统一将字符转为大写计算移位量，再根据原字符的大小写返回结果。主函数通过模运算实现密钥的循环使用，逻辑直白易懂。代码变量命名（如`temp_c`、`temp_k`）明确，适合新手学习模块化编程。

**题解三：作者 - ShirasuAzusaSaikou (赞：1)**
* **点评**：此题解用`tolower`统一处理密钥的大小写，简化计算。核心逻辑`((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] + 26) % 26`直接计算明文，避免了复杂的条件判断。代码利用`ki = (ki + 1) % kl`实现密钥循环，简洁高效。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决Vigenère解密问题时，常见的难点和应对策略如下：
</difficulty_intro>

1.  **关键点1：密钥的循环使用**
    * **分析**：当密文长度大于密钥时，密钥需重复使用。例如，密钥是"abc"，密文有10个字符，则密钥对应位置为a,b,c,a,b,c,a,b,c,a。优质题解多用`i % key_len`（i是密文当前索引）快速定位密钥字符，如`k[i%k.length()]`。
    * 💡 **学习笔记**：模运算（%）是处理循环问题的“万能钥匙”，记住`当前索引 % 长度`即可定位循环位置。

2.  **关键点2：统一处理大小写**
    * **分析**：加密/解密不区分密钥的大小写（如'A'和'a'视为相同移位量），但明文需保持密文的大小写。优质题解通过`toupper`/`tolower`统一转为大写或小写计算移位量，再根据原字符的大小写恢复结果。例如，密文是'F'（大写），计算时转为'F'-'A'=5，密钥是'b'（小写）转为'B'-'A'=1，明文移位量5-1=4，结果为'A'+4='E'（保持大写）。
    * 💡 **学习笔记**：处理大小写问题时，先统一计算再恢复原格式，能避免复杂的条件判断。

3.  **关键点3：循环移位的负数处理**
    * **分析**：若密文字符移位后小于'A'或'a'（如密文是'A'，密钥是'B'，移位量1），需+26回到字母表末尾（'Z'）。优质题解通过`(c_num - k_num + 26) % 26`确保结果非负，例如`(0 - 1 + 26) % 26 = 25`（对应'Z'）。
    * 💡 **学习笔记**：模运算前加26能避免负数，是处理循环问题的常用技巧。

### ✨ 解题技巧总结
<summary_best_practices>
- **统一计算，恢复格式**：先将字符转为统一格式（如大写）计算移位量，再根据原格式恢复，简化逻辑。
- **模运算循环定位**：用`i % key_len`快速定位循环密钥的位置，避免手动重复密钥字符串。
- **模运算防负数**：计算移位量时，用`(x + 26) % 26`确保结果在0-25之间，避免越界。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合优质题解的思路，提炼出一个简洁且完整的核心实现，帮助大家快速掌握整体框架。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了ingu和Sinwind题解的思路，用位运算统一处理大小写，模运算实现密钥循环，代码简洁高效。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    using namespace std;

    int main() {
        string key, cipher;
        cin >> key >> cipher;
        for (int i = 0; i < cipher.size(); ++i) {
            // 计算密钥的移位量（0-25）
            int shift = (key[i % key.size()] & 31) - 1; // 'A'-'Z'和'a'-'z'的&31结果相同（1-26），减1得0-25
            // 计算明文：密文字符 - 移位量（若结果<0则+26）
            int plain_num = (cipher[i] & 31) - 1 - shift; // 密文字符转为0-25（&31-1）
            plain_num = plain_num < 0 ? plain_num + 26 : plain_num;
            // 恢复原大小写：密文字符的大小写决定结果的大小写
            cipher[i] = (cipher[i] >= 'a') ? (plain_num + 'a') : (plain_num + 'A');
        }
        cout << cipher << endl;
        return 0;
    }
    ```
* **代码解读概要**：
    > 代码首先读取密钥和密文。通过`key[i % key.size()]`循环获取密钥字符，用`&31`统一处理大小写（'A'-'Z'和'a'-'z'的ASCII码后5位相同），得到0-25的移位量。然后计算密文字符对应的0-25值，减去移位量，若结果为负则+26。最后根据密文字符的大小写恢复明文的大小写格式。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：作者 - ingu**
* **亮点**：用`&31`位运算统一处理大小写，代码极短且高效。
* **核心代码片段**：
    ```cpp
    int t=(k[i%k.length()]&31)-1;
    c[i]=(c[i]&31)-t>0?c[i]-t:c[i]-t+26;
    ```
* **代码解读**：
    > `k[i%k.length()]&31`将密钥字符（无论大小写）转为1-26（如'A'=1，'a'=1），减1得0-25的移位量`t`。`c[i]&31`同理处理密文字符，得到1-26的值。判断`(c[i]&31)-t>0`：若成立，明文为`c[i]-t`（如'F'（6）-1（t=1）=5→'E'）；否则加26（如'A'（1）-2（t=2）= -1→-1+26=25→'Z'）。这一步直接通过字符的ASCII码计算，无需额外转换。
* 💡 **学习笔记**：位运算（&31）是快速统一大小写的技巧，利用了'A'（65=0b1000001）和'a'（97=0b1100001）后5位相同的特性。

**题解二：作者 - Sinwind**
* **亮点**：将解密逻辑封装为函数，结构清晰，易于维护。
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
    > 函数`decryption`接收密文字符`c`和密钥字符`k`。首先用`toupper`统一转为大写计算移位量：`temp_c`是密文的大写形式（如'f'→'F'），`temp_k`是密钥的大写形式（如'b'→'B'）。然后判断`temp_c >= temp_k`：若成立，明文是`temp_c - temp_k`（如'F'-'B'=4→'E'）；否则加26（如'A'-'B'= -1→'A'+26-'B'=25→'Z'）。最后根据原密文的大小写（`isupper(c)`）决定明文的大小写（'A'或'a'）。
* 💡 **学习笔记**：函数封装能让代码更模块化，便于调试和复用。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解解密过程，我们设计一个“8位像素密码机”动画，用复古风格演示每个字符的解密步骤！
</visualization_intro>

  * **动画演示主题**：`像素密码机：Vigenère解密之旅`

  * **核心演示内容**：展示密文字符逐个解密的过程，包括密钥的循环使用、移位量计算、循环移位的处理。

  * **设计思路简述**：采用8位像素风格（类似FC游戏），用不同颜色的方块表示密文、密钥和明文。关键步骤（如密钥循环、移位计算）用闪烁和音效提示，帮助学习者“看到”每一步逻辑。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          * 屏幕分为三行：顶部是密文（蓝色方块，如`Yvqgpx...`），中间是密钥（红色方块，如`CompleteVictory`），底部是明文（绿色方块，初始为空）。
          * 控制面板有“单步”、“自动播放”按钮和速度滑块（1-5倍速）。

    2.  **密钥循环标记**：
          * 密文第i个字符（蓝色方块）高亮时，密钥的第`i % key_len`个字符（红色方块）同步高亮（如i=3，key_len=3→密钥第0个字符高亮）。

    3.  **移位量计算**：
          * 弹出小窗口显示密钥字符的移位量（如密钥是'B'→显示“移位量：1”），伴随“滴”的音效。

    4.  **循环移位动画**：
          * 密文字符（如'Y'）通过箭头动画向左移动（移位量步长），若超出左边界（如'A'左移1），则从右边界循环（'A'→'Z'），用旋转动画表示循环。

    5.  **明文生成**：
          * 移位后的字符（如'W'）落入明文区（绿色方块），伴随“叮”的胜利音效。

    6.  **自动演示模式**：
          * 点击“AI自动演示”，密码机自动完成所有解密步骤，学习者可观察整体流程。

  * **旁白提示**：
      * （高亮密文和密钥）“当前处理密文第3个字符'g'，对应密钥第0个字符'C'（移位量2）。”
      * （移位动画时）“'g'向左移2位，得到'e'！”
      * （循环移位时）“如果移位后超出'A'，就从'Z'继续，比如'A'左移1位是'Z'哦~”

<visualization_conclusion>
通过这个像素动画，我们能直观看到每个字符的解密过程，理解密钥循环、移位计算和循环处理的核心逻辑！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
Vigenère密码的核心是“循环移位+字符串处理”，这类技巧在其他密码学问题和字符串循环问题中也常见。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      * 凯撒密码（单表移位）：Vigenère是多表移位的扩展，掌握循环移位后可轻松解决单表问题。
      * 字符串循环移位（如“abcde”左移2位→“cdeab”）：用模运算处理循环位置。
      * 周期性字符串匹配（如判断字符串是否由重复子串构成）：用`i % len`定位循环位置。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1914 小书童——密码**
          * 🗣️ **推荐理由**：基础的凯撒密码问题，练习单表移位和循环处理。
    2.  **洛谷 P1328 生活大爆炸版石头剪刀布**
          * 🗣️ **推荐理由**：涉及循环规则的字符串处理，练习模运算的应用。
    3.  **洛谷 P1553 数字反转（升级版）**
          * 🗣️ **推荐理由**：处理数字的循环反转，练习字符串分割与模运算。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，这些经验对我们很有帮助：
</insights_intro>

> **参考经验 (来自 ShirasuAzusaSaikou)**：“在计算移位量时，我一开始没加26，导致结果出现负数，后来通过打印中间变量发现了问题。这让我意识到，处理循环问题时一定要考虑边界情况！”
>
> **点评**：这位作者的经验很实用。在编程中，遇到循环移位问题时，通过`(x + 26) % 26`可以避免负数，而打印中间变量（如移位量、计算结果）是调试的有效手段。

-----

<conclusion>
本次关于“Vigenère密码”的分析就到这里。通过理解循环移位、模运算和字符串处理的核心技巧，相信大家能轻松解决类似问题。记住，多动手写代码、调试，是掌握编程的关键！下次见~ 💪
</conclusion>

-----

---
处理用时：156.86秒