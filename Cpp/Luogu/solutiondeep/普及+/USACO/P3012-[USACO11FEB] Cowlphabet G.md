# 题目信息

# [USACO11FEB] Cowlphabet G

## 题目描述

Like all bovines, Farmer John's cows speak the peculiar 'Cow'

language. Like so many languages, each word in this language comprises a sequence of upper and lowercase letters (A-Z and a-z).  A word is valid if and only if each ordered pair of adjacent letters in the word is a valid pair.

Farmer John, ever worried that his cows are plotting against him, recently tried to eavesdrop on their conversation. He overheard one word before the cows noticed his presence. The Cow language is spoken so quickly, and its sounds are so strange, that all that Farmer John was able to perceive was the total number of uppercase letters, U (1 <= U <= 250) and the total number of lowercase

letters, L (1 <= L <= 250) in the word. 

Farmer John knows all P (1 <= P <= 200) valid ordered pairs of adjacent letters.  He wishes to know how many different valid 

words are consistent with his limited data.  However, since

this number may be very large, he only needs the value modulo

97654321.

约翰家的奶牛用别人听不懂的“牛语”联络。牛语采用英文字母，而且区分大小写。牛 语中的语法中，前后字母的衔接非常重要，存在P个基本组合，每个字母之后只能接固定的 几个字母。 约翰担心奶牛正在密谋反对他，于是最近一直在偷听她们的对话。可是牛语太复杂了， 他只模模糊糊地听到了一个单词，并确定了这个单词中有U个大写字母，L个小写字母。约 翰对这个单词很在意，他想知道，有多少牛语词汇拥有U个大写字母，L个小写字母。由于 这个数字太大了，你只要输出答案取 97654321 的余数就可以了。 输入格式 ? ? 第一行：三个用空格隔开的整数：U，L和P，1 ≤ U, L ≤ 250，1 ≤ P ≤ 200 第二行到P + 1行：第i + 1有两个字母Ai和Bi，表示字母Ai后面可以接Bi，没有一对Ai和 Bi是完全相同的


## 说明/提示

The word Farmer John overheard had 2 uppercase and 2 lowercase letters.  The valid pairs of adjacent letters are AB, ab, BA, ba, Aa, Bb and bB.


The possible words are:

AabB
ABba
abBA
BAab
BbBb
bBAa
bBbB

## 样例 #1

### 输入

```
2 2 7 
AB 
ab 
BA 
ba 
Aa 
Bb 
bB 
```

### 输出

```
7 
```

# AI分析结果

### 综合分析与结论
这些题解均采用动态规划（DP）解决问题，核心在于定义状态和推导转移方程。状态定义多为包含大写字母个数、小写字母个数以及末尾字母信息的三维数组，转移方程依据下一个字母的大小写情况更新状态。各题解在字母编号处理、状态枚举范围和实现细节上有差异，但整体思路一致。

### 所选题解
- **作者：tXX_F（4星）**
    - **关键亮点**：思路清晰，代码规范，对字母编号转换和状态转移的处理简洁明了，注释详细。
- **作者：Usada_Pekora（4星）**
    - **关键亮点**：状态定义直观，转移方程表述清晰，代码结构简单易懂。
- **作者：xu222ux（4星）**
    - **关键亮点**：思路阐述清晰，代码实现中对状态枚举范围的处理较为巧妙，有详细注释。

### 重点代码及核心思想
#### tXX_F 的题解
```cpp
// 字母编号转换函数
inline int Get(char c){
    return c>='a'&&c<='z'?c-'a'+1:c-'A'+1+26;
}
// 主函数部分
signed main(){
    // 输入处理
    cin>>U>>L>>P;
    char s_1,s_2;
    for(register int i=1;i<=P;++i){
        cin>>s_1>>s_2;
        Vec_S[Get(s_1)].push_back(Get(s_2));
    }
    // 初始化
    for(register int i=1;i<=26;++i){
        F[1][0][i]=1;
        F[1][1][i+26]=1;
    }
    // 状态转移
    int len;
    for(register int i=1;i<=U+L;++i)
        for(register int j=0;j<=U;++j)
            for(register int k=1;k<=52;++k){
                len=Vec_S[k].size();
                for(register int p=0;p<len;++p){
                    if(Vec_S[k][p]<=26)
                        (F[i+1][j][Vec_S[k][p]]+=F[i][j][k])%=Mod;
                    else
                        (F[i+1][j+1][Vec_S[k][p]]+=F[i][j][k])%=Mod;
                }
            }
    // 计算答案
    for(register int i=1;i<=52;++i)
        (Answer+=F[U+L][U][i])%=Mod;
    cout<<Answer<<endl;
    return 0;
}
```
核心思想：通过 `Get` 函数将字母转换为编号，用 `Vec_S` 存储合法的字母对。初始化长度为 1 的字符串的状态，然后根据状态转移方程更新不同长度、不同大写字母个数和末尾字母的字符串的方案数，最后累加得到答案。

#### Usada_Pekora 的题解
```cpp
// 主函数部分
int main(){
    // 输入处理
    scanf("%d%d%d",&u,&l,&n);
    gets(c);
    for(int i=1;i<=n;i++){
        gets(c);
        char a=c[0],b=c[1];
        ch[a][++ch[a][0]]=b;
        if(!vis[a]) {vis[a]=1;v[++v[0]]=a;}
        if(!vis[b]) {vis[b]=1;v[++v[0]]=b;}
    }
    // 初始化
    for(int i=1;i<=v[0];i++) {
        if(v[i]<97) f[v[i]][1][0]=1;
        else f[v[i]][0][1]=1;
    }
    // 状态转移
    for(int i=0;i<=u;i++)
        for(int j=0;j<=l;j++)
            for(int k=1;k<=v[0];k++){
                if(f[v[k]][i][j]) 
                    for(int t=1;t<=ch[v[k]][0];t++){
                        int tmp=ch[v[k]][t];
                        if(tmp<97) f[tmp][i+1][j]=(f[tmp][i+1][j]+f[v[k]][i][j])%mod;
                        else f[tmp][i][j+1]=(f[tmp][i][j+1]+f[v[k]][i][j])%mod;
                    }
            }
    // 计算答案
    for(int i=1;i<=v[0];i++)  ans=(ans+f[v[i]][u][l])%mod;
    printf("%d",ans);
    return 0;
}
```
核心思想：用 `ch` 数组存储合法的字母对，`v` 数组记录出现过的字母。初始化出现过的字母的状态，然后根据状态转移方程更新不同大写字母个数、小写字母个数和末尾字母的字符串的方案数，最后累加得到答案。

#### xu222ux 的题解
```cpp
// 字母编号转换函数
int ctoi(char a){
    if(a>='A'&&a<='Z')return a-'A'+1+26;
    return a-'a'+1;
}
// 主函数部分
int main(){
    // 输入处理
    cin>>x>>y>>n;
    for(int i=1;i<=n;i++){
        char a,b;cin>>a>>b;
        v[ctoi(a)].push_back(ctoi(b));
    }
    // 初始化
    for(int i=1;i<=26;i++)f[1][0][i]=1;
    for(int i=27;i<=52;i++)f[1][1][i]=1;
    // 状态转移
    for(int i=1;i<x+y;i++){
        for(int j=min(i,x);j>=max(0,i-y);j--){
            for(int w=1;w<=52;w++){
                for(int o=0;o<v[w].size();o++){
                    int q=v[w][o];
                    if(q<=26){
                        f[i+1][j][q]+=f[i][j][w];
                        f[i+1][j][q]%=mod;
                    }else if(j!=x){
                        f[i+1][j+1][q]+=f[i][j][w];
                        f[i+1][j+1][q]%=mod;
                    }
                }
            }
        }
    }
    // 计算答案
    int ans=0;
    for(int i=1;i<=52;i++){
        ans+=f[x+y][x][i];
        ans%=mod;
    }
    cout<<ans;
    return 0;
}
```
核心思想：通过 `ctoi` 函数将字母转换为编号，用 `v` 数组存储合法的字母对。初始化长度为 1 的字符串的状态，然后根据状态转移方程更新不同长度、不同大写字母个数和末尾字母的字符串的方案数，最后累加得到答案。

### 最优关键思路或技巧
- **状态定义**：使用三维数组存储状态，包含大写字母个数、小写字母个数和末尾字母信息，能全面描述问题状态。
- **字母编号转换**：将字母转换为数字编号，方便存储和处理合法的字母对。
- **边加边取模**：在状态转移过程中及时取模，避免结果溢出。

### 可拓展之处
同类型题多为状态转移类的动态规划问题，如求满足特定条件的路径数、排列组合数等。类似算法套路是根据问题的限制条件定义状态，推导状态转移方程，通过枚举状态进行转移计算。

### 推荐题目
- P1048 [NOIP2005 普及组] 采药
- P1216 [USACO1.5] 数字三角形 Number Triangles
- P1439 【模板】最长公共子序列

### 个人心得
这些题解中未包含个人心得。

---
处理用时：54.80秒