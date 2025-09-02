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

今天我们来一起分析NOIP2012提高组的“Vigenère密码”问题。这道题是经典的字符串解密题，核心是**字符偏移计算**——就像给每个字母“搬家”，根据密钥的指示调整位置，最终找到它们的“明文家”。


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串`（字符转换与偏移处理）

🗣️ **初步分析**：  
字符串处理就像“字母搬家游戏”——每个密文字符需要根据密钥的“搬家指令”（偏移量），回到它的明文位置。比如密钥是`B`（指令“向左搬1步”），密文是`C`，搬1步就回到`B`；如果密文是`A`，搬1步不够（左边没位置），就从右边绕回来，变成`Z`。  

### 核心思路与难点
所有题解的核心都是**逆向计算偏移量**：  
1. **密钥循环用**：用`i % 密钥长度`重复使用密钥（比如密钥`abc`，第4个字符用`a`）；  
2. **偏移量计算**：密文字符减密钥字符的偏移量（避免负数，加26再取模）；  
3. **大小写保持**：明文要和密文大小写一致（比如密文是`C`，明文也是大写；密文是`c`，明文也是小写）。  

核心难点是**处理负数偏移**（比如密文`A`减密钥`B`得-1，需要加26变成25，对应`Z`）和**保持大小写**。解决方案是：将字符转为数字（如`A=0`、`a=0`）计算偏移，再转回字符时恢复大小写。

### 可视化设计思路
我们设计一个**像素字母搬家动画**（FC复古风格）：  
- 每个字母是5x5的像素块（比如`A`用5x5的像素点组成），密钥字符是**蓝色块**，密文字符是**红色块**，明文结果是**绿色块**；  
- 每步高亮当前处理的“红-蓝”字符对，旁边用像素文字显示计算过程（如`C - B = A`或`A - B = -1 +26=25→Z`）；  
- 动画演示红色块“搬家”：向左移动偏移量步数（不够就从右边绕），移动时有**滑动动画**，伴随“叮”的音效；  
- 密钥循环时，蓝色块会**循环闪烁**，提示“密钥用完啦，从头再来！”。


## 2. 精选优质题解参考

我从思路清晰度、代码可读性、算法有效性等维度，筛选了以下评分≥4星的优质题解：

### 题解一：作者ingu（赞：490）
* **点评**：  
  此题解**代码极简**，用`&31`（二进制`11111`）巧妙获取字母顺序（不管大小写，`A/a`都得1，`B/b`得2……`Z/z`得26），直接计算偏移量。思路直击核心，代码可读性极高，是“用技巧简化问题”的典范。

### 题解二：作者ShirasuAzusaSaikou（赞：2）
* **点评**：  
  此题解**逻辑清晰**，用`tolower`统一密钥字符（避免大小写判断），再用公式`(tolower(密文) - 密钥 +26)%26`计算偏移，最后根据密文的大小写恢复结果。代码简洁，容易理解，适合新手学习。

### 题解三：作者qhr2023（赞：4）
* **点评**：  
  此题解**封装性好**，用`m`函数处理所有大小写情况（4种组合：密文大写/小写 × 密钥大写/小写），公式`(c - k +26)%26`直接计算，代码结构清晰，适合学习“如何用函数简化重复逻辑”。


## 3. 核心难点辨析与解题策略

### 关键点1：如何计算正确的偏移量？
- **分析**：密文字符减密钥字符可能为负（如`A`-`B`=-1），需要加26再取模（`(-1+26)%26=25`→`Z`）。  
- **解决方案**：统一用公式`(密文偏移 - 密钥偏移 +26) %26`，确保结果非负。  
- 💡 **学习笔记**：加26是“避免负数的魔法”！

### 关键点2：如何保持大小写一致？
- **分析**：明文的大小写要和密文一致（密文`C`→明文`B`，密文`c`→明文`b`）。  
- **解决方案**：记录密文的大小写（用`isupper(c)`判断），计算偏移时将密文转为小写/大写，最后恢复大小写。  
- 💡 **学习笔记**：先“统一计算”，再“恢复状态”是处理大小写的常用技巧。

### 关键点3：如何循环使用密钥？
- **分析**：密钥长度可能比密文短（比如密钥`abc`，密文有10个字符），需要重复使用密钥。  
- **解决方案**：用`i % 密钥长度`获取当前密钥字符（第`i`个密文对应第`i%len(key)`个密钥）。  
- 💡 **学习笔记**：模运算（`%`）是“循环”的好帮手！

### ✨ 解题技巧总结
1. **字符转数字**：将字母转为0-25的数字（如`A=0`、`a=0`），方便计算偏移；  
2. **公式复用**：用`(c - k +26)%26`统一处理所有偏移情况；  
3. **循环密钥**：`i % len(key)`让密钥“无限循环”；  
4. **保持大小写**：记录密文的大小写，计算后恢复。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
* **说明**：本代码综合了多个优质题解的思路，用最简洁的方式实现所有核心逻辑。
* **完整核心代码**：
```cpp
#include <iostream>
#include <string>
#include <cctype> // 用于isupper/tolower

using namespace std;

int main() {
    string key, cipher;
    cin >> key >> cipher;
    int key_len = key.size();
    for (int i = 0; i < cipher.size(); ++i) {
        // 1. 获取当前密钥字符（循环使用）
        char k_char = key[i % key_len];
        // 2. 记录密文的大小写
        bool is_upper = isupper(cipher[i]);
        // 3. 将密钥和密文转为小写，计算偏移量（0-25）
        int k_offset = tolower(k_char) - 'a';
        int c_offset = tolower(cipher[i]) - 'a';
        // 4. 计算明文偏移量（加26避免负数）
        int m_offset = (c_offset - k_offset + 26) % 26;
        // 5. 恢复大小写，输出明文
        char m_char = is_upper ? ('A' + m_offset) : ('a' + m_offset);
        cout << m_char;
    }
    cout << endl;
    return 0;
}
```
* **代码解读概要**：  
  代码分5步：①循环取密钥字符；②记录密文大小写；③转小写计算偏移；④公式算明文偏移；⑤恢复大小写输出。逻辑清晰，覆盖所有核心难点。


### 优质题解片段赏析

#### 题解一：作者ingu（赞：490）
* **亮点**：用`&31`巧妙获取字母顺序（不管大小写），代码极简。
* **核心代码片段**：
```cpp
int t = (k[i%k.length()] & 31) - 1;
c[i] = (c[i]&31) - t > 0 ? c[i]-t : c[i]-t+26;
```
* **代码解读**：  
  - `k[i%k.length()] &31`：密钥字符的ASCII码&31（二进制`11111`），得到1-26的顺序（`A`→1，`a`→1，`B`→2……）；  
  - `-1`：将顺序转为偏移量（`A`→0，`B`→1……）；  
  - `c[i]&31`：密文字符的顺序（1-26）；  
  - 三元运算符：如果`(密文顺序 - 偏移量) >0`，直接减；否则加26（避免负数）。  
* **学习笔记**：`&31`是利用ASCII码特性的“黑科技”，能快速统一大小写的字母顺序！

#### 题解二：作者ShirasuAzusaSaikou（赞：2）
* **亮点**：用`tolower`统一密钥，避免大小写判断，代码简洁。
* **核心代码片段**：
```cpp
for(auto &i : k) i = tolower(i); // 密钥统一转为小写
for(int i = 0; i < ml; i++){
    cout << (char) (((m[i] >= 'a')? 'a': 'A') + (tolower(m[i]) - k[ki] +26)%26);
    ki = (ki+1)%kl; // 循环密钥
}
```
* **代码解读**：  
  - `for(auto &i : k) i = tolower(i)`：将密钥所有字符转为小写，后续无需再判断密钥的大小写；  
  - `tolower(m[i]) - k[ki]`：密文转小写后减密钥（已小写），得到偏移量；  
  - `(m[i] >= 'a')? 'a': 'A'`：根据密文的大小写，选择明文的起始字符（`a`或`A`）；  
  - `ki = (ki+1)%kl`：循环使用密钥（`kl`是密钥长度）。  
* **学习笔记**：统一转换密钥的大小写，能减少一半的判断逻辑！


## 5. 算法可视化：像素字母搬家动画

### 动画主题：像素字母的“明文回家”之旅（FC复古风格）
我们用HTML5 Canvas实现一个**轻量化动画**，核心功能如下：

### 1. 场景与UI初始化
- 屏幕分为三部分：**密钥区**（上方，蓝色像素块）、**密文区**（中间，红色像素块）、**明文区**（下方，绿色像素块）；  
- 控制面板：`单步`（处理一个字符）、`自动`（按速度播放）、`重置`（回到初始状态）按钮；`速度滑块`（调整自动播放速度，1-5档）；  
- 背景音乐：8位风格的《超级马里奥》轻快BGM（循环播放）。

### 2. 动画核心步骤
- **步骤1：高亮字符对**：当前处理的密文字符（红块）和密钥字符（蓝块）**闪烁**，旁边用像素文字显示`当前密文：C，当前密钥：B`；  
- **步骤2：计算偏移**：用像素文字显示计算过程（如`C(2) - B(1) =1→A`或`A(0)-B(1)=-1+26=25→Z`）；  
- **步骤3：搬家动画**：红色块向左移动`偏移量`步数（比如偏移1步，红块从`C`滑到`B`）；如果不够，从右边绕（比如`A`向左1步，滑到`Z`的位置）；  
- **步骤4：结果显示**：红色块变成绿色块，移动到明文区的对应位置，伴随“叮”的音效。

### 3. 交互与音效
- **单步执行**：点击“单步”按钮，处理一个字符；  
- **自动播放**：点击“自动”按钮，按滑块速度连续处理（1档最慢，5档最快）；  
- **重置**：点击“重置”按钮，所有块回到初始位置；  
- **音效**：处理字符时“叮”，处理负数时“嗒”，完成所有字符时播放“胜利音效”（如FC游戏的通关音乐）。


## 6. 拓展练习与相似问题

### 通用思路迁移
本题的**字符偏移**和**循环密钥**思路，可用于解决：  
1. **凯撒密码解密**（单表密码，密钥是固定偏移量）；  
2. **字符串替换问题**（如将每个字符按规则替换）；  
3. **大小写转换问题**（如保持字符串的大小写不变，仅调整字符内容）。

### 洛谷推荐练习
1. **P1032 字串变换**：考察字符串的规则替换，需要处理字符的位置变换；  
2. **P1081 Substring**：考察字符串的子串查找与替换，需要处理字符的匹配；  
3. **P1102 A-B 数对**：虽然是数学题，但需要处理字符串的输入与转换（将字符串转为数字）；  
4. **P1078 RSA加密**：考察密码学中的字符转换，需要处理大数的模运算（进阶）。


## 7. 学习心得与经验分享

### 来自题解作者的经验
- 作者ingu提到：“用`&31`获取字母顺序，是因为ASCII码中大小写字母的后5位相同，这样可以避免判断大小写。”——**利用字符编码的特性，能简化代码！**  
- 作者ShirasuAzusaSaikou说：“统一密钥的大小写，能减少一半的判断逻辑，避免出错。”——**预处理数据（如统一大小写），是编程的重要技巧！**


## 总结
解决Vigenère密码的关键是**处理字符偏移**、**循环密钥**和**保持大小写**。通过将字符转为数字计算，再转回字符，能轻松解决这些问题。希望这个指南能帮助你掌握字符串处理的核心技巧！  

记住：编程就像“字母搬家”——只要找对“指令”（算法），每个字母都能回到它的“家”（明文）。继续加油，下次我们一起解决更复杂的字符串问题！💪

---
处理用时：99.26秒