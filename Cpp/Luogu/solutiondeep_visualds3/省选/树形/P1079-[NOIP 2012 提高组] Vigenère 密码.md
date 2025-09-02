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

✨ **本题主要考察**：字符串处理（字符循环偏移与大小写保持）

🗣️ **初步分析**：  
解决“Vigenère 密码”问题，核心是**逆向计算字符的循环偏移**。简单来说，就像我们在字母表上“倒着走步”——密钥是“步数”，密文是“终点”，我们需要倒推回“起点”（明文）。比如，密文是`f`（对应字母表第5位，从0开始），密钥是`b`（第1位），那么明文就是`f`倒走1步，得到`e`（第4位）。  

**核心思路**：  
1. 对每个密文字符，找到对应的密钥字符（密钥循环使用，用`i%密钥长度`实现）；  
2. 计算密文与密钥的偏移（密文编号 - 密钥编号 + 26）% 26（加26避免负数）；  
3. 保持明文与密文的大小写一致。  

**核心难点**：  
- 大小写的正确保持（密文大写则明文大写，反之亦然）；  
- 密钥的循环使用（处理密文长度超过密钥的情况）；  
- 循环偏移的正确计算（避免越界，如`A`倒走1步变为`Z`）。  

**可视化设计思路**：  
计划用**8位像素风格**动画展示字符解密过程：  
- 屏幕左侧显示密文字符（如`f`），中间显示密钥字符（如`b`），右侧显示明文结果（如`e`）；  
- 密文字符向左移动，经过密钥字符时，“倒走”对应的步数（动画显示字符逐步变化）；  
- 用颜色高亮当前处理的字符（如密文变红，密钥变蓝），完成后明文变绿；  
- 加入“叮”的音效（每完成一个字符）和“胜利”音效（全部完成），增加趣味性。  


## 2. 精选优质题解参考

为大家筛选了3份**思路清晰、代码简洁**的优质题解，评分均≥4星：


### **题解一：作者@Sinwind（赞：3）**  
* **点评**：  
  这份题解的**函数封装**非常棒！把解密逻辑放在`decryption`函数里，逻辑清晰易懂。处理大小写时，先用`toupper`统一转换密文和密钥（计算偏移时不考虑大小写），再根据密文的大小写决定明文的大小写（用`isupper`判断）。这种“分离计算与大小写处理”的思路，非常适合新手学习，代码可读性很高。  


### **题解二：作者@ShirasuAzusaSaikou（赞：2）**  
* **点评**：  
  代码**极度简洁**！用`tolower`把密钥统一转为小写（避免大小写影响偏移计算），然后通过`(tolower(m[i]) - k[ki] + 26) % 26`计算偏移，最后根据密文的大小写生成明文。这种“统一处理密钥”的技巧，减少了条件判断，代码更紧凑，适合想优化代码长度的同学。  


### **题解三：作者@3_14（赞：0）**  
* **点评**：  
  这份题解的**函数分工明确**！用`charToNum`把字符转为0-25的编号，`numToChar`把编号转回字符，`vigenereDecrypt`处理整个解密过程。这种“模块化”的写法，让代码结构清晰，容易调试，适合学习如何组织复杂逻辑。  


## 3. 核心难点辨析与解题策略

### **1. 难点一：大小写的保持**  
* **问题**：明文必须与密文大小写一致，但密钥的大小写不影响偏移。  
* **解决策略**：  
  计算偏移时，先将密文和密钥统一转为大写（或小写），再根据密文的原始大小写生成明文。例如：  
  ```cpp
  char temp_c = toupper(c); // 密文转大写
  char temp_k = toupper(k); // 密钥转大写
  int offset = (temp_c - temp_k + 26) % 26;
  return isupper(c) ? ('A' + offset) : ('a' + offset); // 保持密文大小写
  ```  
* 💡 **学习笔记**：大小写处理的关键是“分离计算与结果生成”——计算时不考虑大小写，结果时根据原始密文调整。  


### **2. 难点二：密钥的循环使用**  
* **问题**：当密文长度超过密钥时，需要重复使用密钥。  
* **解决策略**：  
  用`i % 密钥长度`获取当前密文字符对应的密钥字符。例如：  
  ```cpp
  for (int i = 0; i < cipher.size(); ++i) {
      char k_char = key[i % key.size()]; // 循环取密钥字符
      // 解密逻辑
  }
  ```  
* 💡 **学习笔记**：取模运算（`%`）是处理“循环”问题的神器，比如循环数组、循环使用资源。  


### **3. 难点三：循环偏移的计算**  
* **问题**：当密文编号小于密钥编号时，会出现负数（如`A`-`B`=-1），需要循环到字母表末尾（`Z`）。  
* **解决策略**：  
  计算时加上26再取模，确保结果非负。例如：  
  ```cpp
  int offset = (c_num - k_num + 26) % 26; // c_num是密文编号，k_num是密钥编号
  ```  
* 💡 **学习笔记**：处理循环问题时，“加周期再取模”是常用技巧，避免负数。  


### ✨ 解题技巧总结  
1. **函数封装**：将重复逻辑（如解密单个字符）封装成函数，提高代码可读性；  
2. **统一处理**：将密钥或密文统一转为大写/小写，减少条件判断；  
3. **取模运算**：处理循环问题（如密钥循环）时，用`%`简化逻辑；  
4. **边界处理**：计算偏移时加26再取模，避免负数。  


## 4. C++核心代码实现赏析

### **本题通用核心C++实现参考**  
* **说明**：综合了@Sinwind和@ShirasuAzusaSaikou的思路，代码简洁且逻辑清晰。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <string>
  #include <cctype>
  using namespace std;

  // 解密单个字符：c是密文，k是密钥
  char decrypt(char c, char k) {
      char temp_c = toupper(c); // 密文转大写（计算偏移）
      char temp_k = toupper(k); // 密钥转大写（计算偏移）
      int offset = (temp_c - temp_k + 26) % 26; // 计算偏移（避免负数）
      return isupper(c) ? ('A' + offset) : ('a' + offset); // 保持密文大小写
  }

  int main() {
      string key, cipher;
      cin >> key >> cipher;
      int key_len = key.size();
      for (int i = 0; i < cipher.size(); ++i) {
          // 循环取密钥字符（i%key_len）
          cout << decrypt(cipher[i], key[i % key_len]);
      }
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. `decrypt`函数：处理单个字符的解密，负责计算偏移和保持大小写；  
  2. 主函数：读取密钥和密文，循环处理每个密文字符，用`i%key_len`循环使用密钥。  


### **针对各优质题解的片段赏析**

#### **题解一（@Sinwind）：函数封装**  
* **亮点**：将解密逻辑封装成函数，逻辑清晰。  
* **核心代码片段**：  
  ```cpp
  char decryption(char c, char k) {
      char temp_c = toupper(c);
      char temp_k = toupper(k);
      char m =(isupper(c)) ? 'A' : 'a';
      m += (temp_c >= temp_k) ? (temp_c - temp_k) : (temp_c + 26 - temp_k);
      return m;
  }
  ```  
* **代码解读**：  
  - 先将密文和密钥转为大写（`toupper`）；  
  - 根据密文的大小写，初始化明文的起始字符（`'A'`或`'a'`）；  
  - 计算偏移：如果密文大于等于密钥，直接减；否则加26再减（避免负数）。  
* 💡 **学习笔记**：函数封装能让代码更模块化，容易调试。  


#### **题解二（@ShirasuAzusaSaikou）：统一密钥处理**  
* **亮点**：用`tolower`统一密钥为小写，减少条件判断。  
* **核心代码片段**：  
  ```cpp
  for(auto &i : k) i = tolower(i); // 密钥转为小写
  for(int i = 0; i < ml; i++){
      cout <<(char) (((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] + 26) % 26);
      ki = (ki + 1) % kl;
  }
  ```  
* **代码解读**：  
  - 先将密钥转为小写（`tolower`）；  
  - 计算偏移时，将密文转为小写（`tolower(m[i])`），减去密钥字符（已小写），加26再取模；  
  - 根据密文的大小写，生成明文（`'a'`或`'A'`加偏移）。  
* 💡 **学习笔记**：统一处理密钥可以减少条件判断，让代码更简洁。  


#### **题解三（@3_14）：模块化处理**  
* **亮点**：用多个函数分工处理字符转换和解密。  
* **核心代码片段**：  
  ```cpp
  int charToNum(char c) {
      return c >= 'A' && c <= 'Z' ? c - 'A' : c - 'a';
  }
  char numToChar(int num, bool isUpper) {
      return isUpper ? 'A' + num : 'a' + num;
  }
  string vigenereDecrypt(const string& ciphertext, const string& key) {
      string plaintext;
      for (int i = 0; i < ciphertext.size(); ++i) {
          int cNum = charToNum(ciphertext[i]);
          int kNum = charToNum(key[i % key.size()]);
          int mNum = (cNum - kNum + 26) % 26;
          plaintext.push_back(numToChar(mNum, isupper(ciphertext[i])));
      }
      return plaintext;
  }
  ```  
* **代码解读**：  
  - `charToNum`：将字符转为0-25的编号；  
  - `numToChar`：将编号转回字符（根据大小写）；  
  - `vigenereDecrypt`：处理整个解密过程，循环调用上述函数。  
* 💡 **学习笔记**：模块化处理能让代码结构更清晰，适合复杂逻辑。  


## 5. 算法可视化：像素动画演示 (核心部分)

### **动画演示主题**：字母表“倒走步”游戏（8位像素风格）

### **核心演示内容**：  
展示密文字符`f`（小写）用密钥`b`（小写）解密为`e`（小写）的过程。

### **设计思路**：  
采用8位像素风格（类似FC红白机），用简单的图形和音效增强趣味性，让同学们直观看到“倒走步”的过程。

### **动画帧步骤与交互关键点**：  
1. **场景初始化**：  
   - 屏幕左侧显示密文字符`f`（红色像素块）；  
   - 中间显示密钥字符`b`（蓝色像素块）；  
   - 右侧显示空白区域（用于显示明文）；  
   - 底部有“开始”“单步”“重置”按钮，以及速度滑块。  

2. **算法启动**：  
   - 点击“开始”，密文字符`f`向左移动，靠近密钥字符`b`；  
   - 同时，屏幕上方显示文字提示：“密文`f`（编号5）要倒走`b`（编号1）步”。  

3. **核心步骤演示**：  
   - 密文字符`f`与密钥字符`b`碰撞，开始“倒走”：  
     - 第1帧：`f`变为`e`（绿色像素块）；  
     - 同时，播放“叮”的音效；  
     - 屏幕上方显示文字提示：“5 - 1 = 4，对应`e`”。  

4. **结果展示**：  
   - 明文`e`移动到右侧空白区域；  
   - 播放“胜利”音效（短上扬音调）；  
   - 屏幕显示“解密成功！”的文字提示。  

5. **交互控制**：  
   - “单步”按钮：逐帧观看解密过程；  
   - “速度滑块”：调整动画播放速度（从慢到快）；  
   - “重置”按钮：恢复初始状态，重新演示。  

### **为什么这样设计？**  
- 像素风格：营造复古游戏氛围，降低学习压力；  
- 颜色高亮：清晰区分密文、密钥、明文，突出变化；  
- 音效提示：强化关键操作的记忆（如“叮”表示完成一个字符）；  
- 文字提示：解释每一步的逻辑，帮助理解“为什么这样做”。  


## 6. 拓展练习与相似问题思考

### **通用思路/技巧迁移**  
本题的**字符循环偏移**和**大小写处理**技巧，可用于以下场景：  
1. **加密算法**：如Caesar密码（单表循环偏移）、Vigenère密码（多表循环偏移）；  
2. **字符串转换**：如将字符串中的字符按指定规则移位（如P1088火星人）；  
3. **密码学问题**：如解密简单的替代密码（如P1200你的飞碟在这儿）。  


### **练习推荐 (洛谷)**  
1. **洛谷 P1088** - 火星人  
   - 🗣️ **推荐理由**：需要处理字符串的循环移位，类似本题的循环偏移，能巩固“取模运算”和“字符转换”技巧。  
2. **洛谷 P1102** - A-B问题  
   - 🗣️ **推荐理由**：需要处理字符串的字符减法，类似本题的偏移计算，能巩固“边界处理”（避免负数）技巧。  
3. **洛谷 P1200** - [USACO1.1]你的飞碟在这儿Your Ride Is Here  
   - 🗣️ **推荐理由**：需要将字符串中的字符转换为数字并计算乘积，类似本题的“字符编号”技巧，能巩固“字符与数字的转换”。  


## 7. 学习心得与经验分享 (若有)

### **参考经验 (来自@ShirasuAzusaSaikou)**  
> “建议这里细心做，不然容易出错，别问我咋知道。（逃）”  

**点评**：  
这位作者的经验很实在！在处理字符串转换问题时，**细心**是关键——比如大小写的判断、偏移的计算（是否加26）、密钥的循环使用（是否用对`%`）。如果粗心，很容易出现“差1错误”（如编号从1开始 instead of 0）或“大小写错误”（如明文大写变成小写）。  

**借鉴意义**：  
- 写代码前，先理清逻辑（如编号从0还是1开始）；  
- 写完代码后，用样例测试（如本题的样例输入`CompleteVictory`和`Yvqgpxaimmklongnzfwpvxmniytm`，输出`Wherethereisawillthereisaway`）；  
- 如果出错，用`cout`打印中间变量（如密文编号、密钥编号、偏移），定位错误。  


## 结语  
本次关于“Vigenère 密码”的分析就到这里！希望大家能掌握**字符循环偏移**和**大小写处理**的技巧，在后续的字符串问题中举一反三。记住：**细心+模块化**是解决字符串问题的关键！下次我们再一起探索新的编程挑战！💪

---
处理用时：198.73秒