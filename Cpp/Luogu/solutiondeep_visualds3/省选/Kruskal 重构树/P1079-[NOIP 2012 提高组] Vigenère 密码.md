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


今天我们来一起分析**NOIP 2012提高组第一天第一题——Vigenère密码**。这道题是字符串处理与模拟的经典题目，能帮大家巩固“按规则逐个处理字符”的核心技巧。


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟` (字符串处理) + `编程技巧应用`


🗣️ **初步分析**：  
解决这道题的关键，就像给字母们“调座位”——密文里的每个字母，要根据密钥的指示**往左挪若干位**（比如密钥是`B`就挪1位，`C`挪2位……）。如果挪到`A`或`a`还不够，就绕到`Z`或`z`继续（类似“循环队列”）。  

**核心算法**：模拟解密规则——对每个密文字符，结合循环使用的密钥字符，计算偏移量，调整得到明文（保持原大小写）。  
**核心难点**：  
1. 密钥要循环使用（密文比密钥长时，反复用密钥）；  
2. 保持明文与密文的大小写一致；  
3. 偏移后避免出现“小于A/a”的字符（比如`A-1`要变成`Z`）。  

**解决思路**：  
- 用`i % 密钥长度`实现密钥循环；  
- 记录密文的大小写（比如用`isupper`判断），解密后保持相同大小写；  
- 偏移时用`(密文编号 - 密钥编号 + 26) % 26`避免负数（加26再取模，确保结果非负）。  


## 2. 精选优质题解参考

为大家筛选了**4篇评分≥4星**的优质题解，覆盖不同思路，适合不同学习阶段的同学：


### 题解一：(作者：ingu，赞：490，评分：5星)  
**点评**：这道题的“最短代码”天花板！作者用`x & 31`的技巧（利用ASCII码中大小写字母后5位相同）快速得到字母的顺序（A/a对应1，B/b对应2……Z/z对应26），再用`c[i] - t`或`c[i] - t + 26`处理偏移，代码简洁到“极致”，却完美覆盖所有规则。适合想学习**ASCII技巧**的同学。


### 题解二：(作者：LightCoder，赞：33，评分：4星)  
**点评**：用`队列(queue)`模拟密钥表的生成，思路非常直观——就像把字母排成一队，每次把队头移到队尾，生成下一行的密钥表。这种“打表”方法适合刚学字符串的同学，能**可视化理解密钥表的规律**，但代码略长。


### 题解三：(作者：qhr2023，赞：4，评分：4星)  
**点评**：用`函数封装`处理每个字符的解密，把大小写判断、偏移计算写成独立函数`m()`，主函数只需要循环调用。代码结构清晰，适合学习**模块化编程**，避免重复代码。


### 题解四：(作者：3_14，赞：0，评分：4星)  
**点评**：把“字符转数字”“数字转字符”“解密逻辑”拆分成三个函数，完全分离了不同功能，代码可读性极高。适合想学习**函数设计**的同学，尤其是如何把复杂问题拆解成小问题。


## 3. 核心难点辨析与解题策略

### 关键点1：密钥的循环使用  
**问题**：密文长度可能远大于密钥长度，如何反复用密钥？  
**解决**：用`i % 密钥长度`（比如第`i`个密文字符对应密钥的`i % key_len`位）。  
**学习笔记**：循环问题优先想“取模”！


### 关键点2：保持大小写一致  
**问题**：密文是大写，明文也要大写；密文是小写，明文也要小写。  
**解决**：  
- 方法1：记录密文的大小写状态（比如用`isUpper = (c >= 'A' && c <= 'Z')`），解密后根据状态加`'A'`或`'a'`；  
- 方法2：直接用密文的ASCII码减去偏移量，再判断是否小于`'A'`或`'a'`（比如`c[i] - t < 'A'`就加26）。  
**学习笔记**：大小写判断用`isupper`/`islower`更可靠！


### 关键点3：偏移的边界处理  
**问题**：密文编号减密钥编号可能得到负数（比如`A-1`），如何变成`Z`？  
**解决**：用`(密文编号 - 密钥编号 + 26) % 26`（加26确保结果非负，再取模26回到0-25范围）。  
**学习笔记**：处理“循环边界”用`+周期数再取模`！


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
**说明**：综合了`3_14`的函数分离思想和`qhr2023`的大小写处理，代码结构清晰，适合入门。  
**完整核心代码**：  
```cpp
#include <iostream>
#include <string>
#include <cctype> // 用于isupper、tolower等函数
using namespace std;

// 将字符转换为0-25的编号（A/a→0，B/b→1，…，Z/z→25）
int charToNum(char c) {
    if (isupper(c)) return c - 'A';
    else return c - 'a';
}

// 将编号转换为字符（根据isUpper决定大写/小写）
char numToChar(int num, bool isUpper) {
    if (isUpper) return 'A' + num;
    else return 'a' + num;
}

// 解密单个字符：key_char是密钥字符，cipher_char是密文字符
char decryptChar(char key_char, char cipher_char) {
    bool isUpper = isupper(cipher_char); // 记录密文的大小写
    int key_num = charToNum(key_char);   // 密钥字符的编号（0-25）
    int cipher_num = charToNum(cipher_char); // 密文字符的编号（0-25）
    // 解密公式：明文编号 = (密文编号 - 密钥编号 + 26) % 26
    int plain_num = (cipher_num - key_num + 26) % 26;
    return numToChar(plain_num, isUpper); // 转换为字符，保持原大小写
}

int main() {
    string key, cipher;
    cin >> key >> cipher;
    int key_len = key.size();
    for (int i = 0; i < cipher.size(); ++i) {
        // 密钥循环使用：第i个密文字符对应密钥的i%key_len位
        char key_char = key[i % key_len];
        char plain_char = decryptChar(key_char, cipher[i]);
        cout << plain_char;
    }
    return 0;
}
```
**代码解读概要**：  
1. `charToNum`：把大小写字母转换为0-25的编号（统一处理，避免大小写判断）；  
2. `numToChar`：把编号转换为字符，根据`isUpper`保持原大小写；  
3. `decryptChar`：核心解密逻辑，计算偏移量；  
4. 主函数：循环处理每个密文字符，用`i%key_len`循环使用密钥，输出明文。


### 各优质题解的片段赏析

#### 题解一（作者：ingu）  
**亮点**：用`&31`快速得到字母顺序（ASCII技巧）。  
**核心代码片段**：  
```cpp
for (int i=0; i<c.length(); i++) {
    int t = (k[i%k.length()] & 31) - 1; // 密钥字符的偏移量（A/a对应0，B/b对应1，…）
    c[i] = (c[i] & 31) - t > 0 ? c[i] - t : c[i] - t + 26;
}
```
**代码解读**：  
- `k[i%k.length()] & 31`：大写字母`A`是65（二进制`01000001`），`&31`（二进制`00011111`）得到1；小写`a`是97（`01100001`），`&31`也得到1。所以不管大小写，都能得到字母的顺序（A/a→1，B/b→2，…，Z/z→26）。  
- `(c[i] & 31) - t > 0`：判断密文编号减密钥编号是否大于0（比如`H&31=8`，`a&31=1`，`8-1=7>0`，直接减；如果是`A&31=1`，`b&31=2`，`1-2=-1`，就加26）。  
**学习笔记**：`x & 31`是处理大小写字母的“神技巧”！


#### 题解二（作者：LightCoder）  
**亮点**：用队列模拟密钥表生成（直观理解密钥表规律）。  
**核心代码片段**：  
```cpp
queue<int> q;
for (int i=1; i<=26; i++) q.push(i); // 初始化队列：1→A，2→B，…，26→Z
for (int i=1; i<=26; i++) {
    int Mid = q.front();
    q.push(Mid); q.pop(); // 把队头移到队尾，生成下一行
    for (int j=26; j>=1; j--) {
        Map[i][j] = q.front(); // 填充密钥表
        q.push(q.front()); q.pop(); // 保持队列顺序
    }
}
```
**代码解读**：  
- 队列初始是`1→2→…→26`（对应A→Z）；  
- 每次循环把队头移到队尾（比如第一行后，队列变成`2→3→…→26→1`，对应第二行的密钥表）；  
- 用`Map[i][j]`存储密钥表，`i`是密钥字符，`j`是明文字符，`Map[i][j]`是密文字符。  
**学习笔记**：队列适合模拟“循环移动”的场景！


#### 题解三（作者：qhr2023）  
**亮点**：用函数封装处理大小写（简洁）。  
**核心代码片段**：  
```cpp
char m(char k, char c) {
    if (k >= 'a' && c >= 'a') return (c - k + 26) % 26 + 'a';
    else if (k >= 'a' && c <= 'Z') return (c - 'A' - (k - 'a') + 26) % 26 + 'A';
    else if (k <= 'Z' && c >= 'a') return (c - 'a' - (k - 'A') + 26) % 26 + 'a';
    else return (c - k + 26) % 26 + 'A';
}
```
**代码解读**：  
- 分四种情况处理大小写组合（密钥大写/小写，密文大写/小写）；  
- 用`+26`再取模避免负数；  
- 直接返回解密后的字符，主函数只需循环调用。  
**学习笔记**：函数封装能减少重复代码！


## 5. 算法可视化：像素动画演示

### 设计思路  
用**8位像素风格**模拟解密过程，把每个字符的变化做成“动画”，结合音效和交互，让抽象的“偏移”变直观！


### 动画方案细节

#### 1. 界面布局（像素风格）  
- **顶部**：显示密文字符串（比如`Yvqgpxaimmklongnzfwpvxmniytm`），每个字符是一个16x16的像素块，用蓝色显示；  
- **中间**：显示密钥字符串（比如`CompleteVictory`），循环部分用闪烁的黄色标记；  
- **底部**：显示明文字符串（实时更新，用绿色显示）；  
- **右侧控制面板**：`单步执行`、`自动播放`、`重置`按钮，`速度滑块`（1-5倍速）。


#### 2. 动画步骤  
1. **初始化**：密文、密钥、明文区域显示初始内容，播放8位风格的背景音乐（比如《超级马里奥》的小关卡音乐）；  
2. **单步执行**：  
   - 高亮当前处理的密文字符（蓝色→红色）；  
   - 高亮对应的密钥字符（黄色→橙色）；  
   - 用动画显示密文字符“往左移动n位”（比如密钥是`B`，密文`Y`→`X`→`W`，移动时伴随“叮”的音效）；  
   - 如果移动到`A`以下（比如`A-1`），动画显示“跳到`Z`”（伴随“嗒”的音效）；  
   - 明文字符区域显示结果（绿色像素块）；  
3. **自动播放**：按设定速度依次处理所有字符，完成后播放“胜利音效”（比如《塞尔达传说》的解谜成功音效）；  
4. **重置**：回到初始状态，重新开始。


#### 3. 游戏化元素  
- **关卡设计**：把密文分成5段，每处理一段算“过一关”，通关后显示“Level 1 Clear!”的像素弹窗；  
- **积分奖励**：单步执行无错误得10分，自动播放无错误得20分，累计积分可解锁“隐藏皮肤”（比如密文字符变成马里奥的帽子）；  
- **音效**：  
  - 处理一个字符：“叮”（高频短音）；  
  - 完成一段：“嗒”（低频长音）；  
  - 全部完成：“噔噔噔”（胜利旋律）。


## 6. 拓展练习与相似问题

### 相似问题  
1. **洛谷P1085 不高兴的津津**：模拟津津的学习时间，锻炼“按规则循环处理”的能力；  
2. **洛谷P1102 A-B 数对**：字符串处理与数值转换，锻炼“字符转数字”的技巧；  
3. **洛谷P1200 你的飞碟在这儿**：字符与数字的映射，类似Vigenère密码的“字符编号”问题；  
4. **洛谷P1553 数字反转**：处理字符串的反转，锻炼“边界条件”（比如前导零）。


## 7. 学习心得与经验分享

### 来自题解的启发  
1. **ASCII技巧**：`x & 31`能快速得到字母顺序（避免大小写判断），`tolower`/`toupper`能统一处理大小写；  
2. **模块化编程**：把复杂逻辑拆成函数（比如`charToNum`、`decryptChar`），代码更易读；  
3. **边界处理**：遇到“循环问题”（比如字母表），用`+周期数再取模`（比如+26再%26）避免负数。


## 💪 总结  
Vigenère密码的核心是**模拟解密规则**，关键是处理“循环密钥”“大小写”“边界偏移”三个问题。通过这道题，大家能学会：  
- 字符串的循环处理（`i%len`）；  
- 字符的ASCII操作；  
- 函数封装与模块化编程。  

多做类似的字符串模拟题，就能熟练掌握这些技巧啦！下次我们再一起挑战更难的题目～ 😊

---
处理用时：104.58秒