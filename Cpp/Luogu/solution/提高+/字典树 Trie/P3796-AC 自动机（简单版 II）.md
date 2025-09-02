# AC 自动机（简单版 II）

## 题目描述

有 $N$ 个由小写字母组成的模式串以及一个文本串 $T$。每个模式串可能会在文本串中出现多次。你需要找出**哪些**模式串在文本串 $T$ 中出现的次数最多。


## 样例 #1

### 输入

```
2
aba
bab
ababababac
6
beta
alpha
haha
delta
dede
tata
dedeltalphahahahototatalpha
0```

### 输出

```
4
aba
2
alpha
haha```

# 题解

## 作者：yybyyb (赞：212)

依旧是AC自动机的模板题

其实和（简单）的那个模板题是一样的

只需要把最终求解的东西修改一下即可

其他的都写在注释里面了

AC自动机是个好东西。。。

但是我自己打的时候不知道为啥，容易TLE。。

可能是我写的太丑了。。。。

顺带把博客链接搞一下把

[如果不太懂AC自动机可以看一下](http://www.cnblogs.com/cjyyb/p/7196308.html)

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
struct Tree//字典树 
{
     int fail;//失配指针
     int vis[26];//子节点的位置
     int end;//标记以这个节点结尾的单词编号 
}AC[100000];//Trie树
int cnt=0;//Trie的指针 
struct Result
{
      int num;
      int pos;
}Ans[100000];//所有单词的出现次数 
bool operator <(Result a,Result b)
{
      if(a.num!=b.num)
         return a.num>b.num;
      else
         return a.pos<b.pos;
}
string s[100000];
inline void Clean(int x)
{
       memset(AC[x].vis,0,sizeof(AC[x].vis));
       AC[x].fail=0;
       AC[x].end=0;
}
inline void Build(string s,int Num)
{
        int l=s.length();
        int now=0;//字典树的当前指针 
        for(int i=0;i<l;++i)//构造Trie树
        {
                if(AC[now].vis[s[i]-'a']==0)//Trie树没有这个子节点
                {
                   AC[now].vis[s[i]-'a']=++cnt;//构造出来
                   Clean(cnt);
                }
                now=AC[now].vis[s[i]-'a'];//向下构造 
        }
        AC[now].end=Num;//标记单词结尾 
}
void Get_fail()//构造fail指针
{
        queue<int> Q;//队列 
        for(int i=0;i<26;++i)//第二层的fail指针提前处理一下
        {
               if(AC[0].vis[i]!=0)
               {
                   AC[AC[0].vis[i]].fail=0;//指向根节点
                   Q.push(AC[0].vis[i]);//压入队列 
               }
        }
        while(!Q.empty())//BFS求fail指针 
        {
              int u=Q.front();
              Q.pop();
              for(int i=0;i<26;++i)//枚举所有子节点
              {
                        if(AC[u].vis[i]!=0)//存在这个子节点
                      {
                                AC[AC[u].vis[i]].fail=AC[AC[u].fail].vis[i];
                                    //子节点的fail指针指向当前节点的
                                  //fail指针所指向的节点的相同子节点 
                                Q.push(AC[u].vis[i]);//压入队列 
                      }
                      else//不存在这个子节点 
                      AC[u].vis[i]=AC[AC[u].fail].vis[i];
                      //当前节点的这个子节点指向当
                      //前节点fail指针的这个子节点 
              }
        }
}
int AC_Query(string s)//AC自动机匹配
{
        int l=s.length();
        int now=0,ans=0;
        for(int i=0;i<l;++i)
        {
                now=AC[now].vis[s[i]-'a'];//向下一层
                for(int t=now;t;t=AC[t].fail)//循环求解
                         Ans[AC[t].end].num++;
        }
        return ans;
}
int main()
{
     int n;
     while(233)
     {
          cin>>n;
          if(n==0)break;
          cnt=0;
          Clean(0);
         for(int i=1;i<=n;++i)
         {
                 cin>>s[i];
                 Ans[i].num=0;
                 Ans[i].pos=i;
                 Build(s[i],i);
         }
         AC[0].fail=0;//结束标志 
         Get_fail();//求出失配指针
         cin>>s[0];//文本串 
         AC_Query(s[0]);
         sort(&Ans[1],&Ans[n+1]);
         cout<<Ans[1].num<<endl;
         cout<<s[Ans[1].pos]<<endl;
         for(int i=2;i<=n;++i)
         {
                if(Ans[i].num==Ans[i-1].num)
                  cout<<s[Ans[i].pos]<<endl;
                else
                   break;
         }
     }
     return 0;
}
```

---

## 作者：FlashHu (赞：82)

先膜一发 [yyb巨佬](https://www.luogu.org/space/show?uid=21283) orz

没错，上面就是他的题解。

依旧是模板，想学ac自动机的话，再次推荐一下[yyb巨佬的博客](http://www.cnblogs.com/cjyyb/p/7196308.html)，本蒟蒻也是从那里开始学的。

上面对此题基本的思路都讲得挺好的。这里只是作一个小小的补充，毕竟蒟蒻真的被TLE搞怕了，连yyb巨佬也不能幸免。。。。。。

用传统方法匹配时，每走到一个新位置，都是要统计答案的。怎么统计呢？暴力跳$fail$，把沿路上能够产生答案的算上，直到跳到根才停下来。这里的时间复杂度是 $O(\sum70|T|)$，在有多组数据的情况下其实是很吃亏的。（蒟蒻用了$fread$，根据目测，最大的一个点输入大小在$30MB$以上！！！）或许这里就是TLE的恶魔。。。。。。

我们发现，在暴跳的过程中，走到的很多节点，对答案是没有贡献的。很自然的想到，这些点可不可以直接跳过呢？或者说，一段没有贡献的路径，我们可不可以把它像并查集一样搞一个路径压缩呢？

因为每个点有且仅有惟一的$fail$，所以这样做是可行的！我们设一个状态$g[i]$，表示沿着$i$向上跳$fail$跳到的第一个能对答案产生贡献的位置（也就是某个单词结尾的$end$位置），找不到的话当然设为虚根$0$了。此状态可以通过递推得到，在求$fail$的时候也一起推出来了。

有了这个想法，具体推法也就很明显了。如果$fail[i]$为某单词结尾，那么$g[i]=fail[i]$。否则$g[i]=g[fail[i]]$。

统计答案就不跳$fail$了，而是跳$g$，同样是跳到根为止。

这种优化实际复杂度并没有变（最坏情况下是一样的），但是实际效果还是挺好的,比较大的点可以优化$25\%$以上。

实在TLE的话， $fread,fwrite,register,inline,$~~O2~~套餐奉上。。。。。。

~~我不会告诉大家yyb\_test 896ms成功冲到了rank1。。。。。。（对你没看错，是yyb\_test而不是FlashHu）~~

附上数组版代码，~~可能有点丑~~
```cpp
#include<cstdio>
#include<cstring>
#define now c[u][*p-'a']
#define skip while(*++p<=' ')//跳过空字符
const int N=1000009;
char s[N<<6],o[N<<4],*m[159];//m存每个模式串的起始位置指针
int c[N][26],f[N],e[N],g[N],q[N],a[159];
//f即fail,e即end,q队列,g如上描述
int main()
{
    fread(s,1,sizeof(s),stdin);//奇技淫巧之fread
    register char *p=s,*p1=o;//p读入，p1输出
    register int n,cnt,i,h,t,u,v,mx;
    while((n=*p&15))
    {
        while(*++p>='0')
            n*=10,n+=*p&15;
        cnt=h=t=0;
        //建自动机开始
        for(i=1;i<=n;++i)
        {
            skip;m[i]=p;
            for(u=0;*p>='a';++p)
                u=now?now:(now=++cnt);
            e[u]=i;//end存的是模式串编号而不是个数了
        }
        skip;m[i]=p;
        //bfs开始，求fail以及g
        for(i=0;i<26;++i)//第一层提前处理
            if(c[0][i])q[++t]=c[0][i];
        while(h<t)
        {
            u=q[++h];
            for(i=0;i<26;++i)
                if((v=c[u][i]))
                {
                    f[q[++t]=v]=c[f[u]][i];
                    g[v]=e[f[v]]?f[v]:g[f[v]];
                }
                else c[u][i]=c[f[u]][i];//把空儿子置为fail的对应儿子，匹配的时候方便点
        }
        //匹配开始
        for(u=0;*p>='a';++p)
            for(v=u=now;v;v=g[v])//沿着g统计答案
                ++a[e[v]];
        //统计答案开始，其实不用sort，扫一遍就好啦
        mx=t=0;
        for(i=1;i<=n;++i)
            if(mx<a[i])mx=a[q[t=1]=i];
            else if(mx==a[i])q[++t]=i;
        //输出答案开始
        sprintf(p1,"%d\n",mx);
        while(*++p1);
        for(i=1;i<=t;++i)
        {
            memcpy(p1,m[q[i]],m[q[i]+1]-m[q[i]]);//我也不知道为什么这里用strcpy会MLE，难道产生了缓存空间？！
            p1+=m[q[i]+1]-m[q[i]];
        }//记得多组数据，弄完一组全清空
        memset(c,0,++cnt*104);
        memset(f,0,cnt<<2);
        memset(e,0,cnt<<2);
        memset(g,0,cnt<<2);
        memset(a,0,(n+1)<<2);
        skip;
    }
    fwrite(o,1,p1-o,stdout);//奇技淫巧之fwrite
    return 0;
}
```

### update:

突然想到$fail$的形态是一棵树，那么$g$显然也是，那么匹配的每个点不就是对在$g$树上的一条链上的所有点产生$1$的贡献吗？何必还要暴力跳，直接把贡献暂时存起来最后再做一遍树形DP不就行了么。。。。。。

复杂度成功降至线性$O(\sum|S|+\sum|T|)$

```cpp
#include<cstdio>
#include<cstring>
#define R register
#define now c[u][*p-'a']
#define skip while(*++p<=' ')//跳过空字符
const int N=159,S=20009,T=1000009;
char s[T<<6],o[T],*m[N];//m存每个模式串的起始位置指针
int c[S][26],f[S],e[S],g[S],q[S],a[N],he[N],ne[N],to[N];
//f即fail,e即end,q队列,g如上描述
void dp(R int x){
    for(R int i=he[x];i;i=ne[i])
        dp(to[i]),a[x]+=a[to[i]];
}
int main()
{
    fread(s,1,sizeof(s),stdin);//奇技淫巧之fread
    R char *p=s,*p1=o;//p读入，p1输出
    R int n,cnt,i,h,t,pe,u,v,mx;
    while((n=*p&15))
    {
        while(*++p>='0')
            n*=10,n+=*p&15;
        cnt=h=t=pe=0;
        //建自动机开始
        for(i=1;i<=n;++i)
        {
            skip;m[i]=p;
            for(u=0;*p>='a';++p)
                u=now?now:(now=++cnt);
            at[e[u]=i]=u;//end存的是模式串编号而不是个数了
        }
        skip;m[i]=p;
        //bfs开始，求fail以及g
        for(i=0;i<26;++i)//第一层提前处理
            if(c[0][i])q[++t]=c[0][i];
        while(h<t)
        {
            if(e[u=q[++h]])
                to[++pe]=e[u],ne[pe]=he[e[g[u]]],he[e[g[u]]]=pe;
            for(i=0;i<26;++i)
                if((v=c[u][i]))
                {
                    f[q[++t]=v]=c[f[u]][i];
                    g[v]=e[f[v]]?f[v]:g[f[v]];
                }
                else c[u][i]=c[f[u]][i];//把空儿子置为fail的对应儿子，匹配的时候方便点
        }
        //匹配开始
        for(u=0;*p>='a';++p)
            u=now,++a[e[u]?e[u]:e[g[u]]];
        //统计答案开始，其实不用sort，扫一遍就好啦
        dp(0);
        mx=t=0;
        for(i=1;i<=n;++i)
            if(mx<a[i])mx=a[q[t=1]=i];
            else if(mx==a[i])q[++t]=i;
        //输出答案开始
        sprintf(p1,"%d\n",mx);
        while(*++p1);
        for(i=1;i<=t;++i)
        {
            memcpy(p1,m[q[i]],m[q[i]+1]-m[q[i]]);//我也不知道为什么这里用strcpy会MLE，难道产生了缓存空间？！
            p1+=m[q[i]+1]-m[q[i]];
        }//记得多组数据，弄完一组全清空
        memset(c,0,++cnt*104);
        memset(f,0,cnt<<2);
        memset(e,0,cnt<<2);
        memset(g,0,cnt<<2);
        memset(a,0,++n<<2);
        memset(he,0,n<<2);
        skip;
    }
    fwrite(o,1,p1-o,stdout);//奇技淫巧之fwrite
    return 0;
}
```

---

## 作者：wxk01 (赞：59)

AC自动机是结合了KMP的失配指针和TRIE的树形结构的一种算法。

（所以我们要把KMP和TRIE先搞明白）


- 
AC自动机
--

~~就是能自动AC的机器~~

	
 AC自动机有三个部分，分别是建树，获取失配指针和查询。
    
   先建一棵TRIE树，再把TRIE树上每个节点的失配指针（重点中的重点）求出，最后查询文本。
    
   首先 我们需要定义一些需要用的数组。
    
         int num[300010];//结点编号
         int ch[300010][26];//子结点
         int fail[300010];//失配指针
         int ans[300010];//答案
- 
建树
--
这是一个裸TRIE。直接贴代码。

```cpp
	void insert(string s,int v){
    	int now=0;//当前访问的节点
    	for(int i=0;i<s.size();i++){
	        int o=s[i]-'a';
    	    if(!ch[now][o])ch[now][o]=++siz;//新编号
        	now=ch[now][o];//继续访问
    	}
    	num[now]=v;//标记
	}
```

- 
获取失配指针
--
	AC自动机的fail[a]=b且b!=root，则a和b所代表的字符相同且a的父结点的fail值为b的父节点。
    
    嗯，文字难免有些令人费解，我们把它转化成代码。
    
	```
	fail[v]=ch[fail[u][i];
	```
    其中v是u的编号为i的子节点。
    
    可是，如果v不存在呢？也就是说，如果u没有编号为i的子节点呢？
    
    那么我们就把u的编号为i的节点直接设为fail[u]的编号为i的子节点。代码：
    ```
	ch[u][i]=ch[fail[u]][i];
```
    
    另外，与root相连的所有结点的fail值为0。

      代码奉上。

     	 
          void getfail(){
              int now=0;//当前访问
              queue<int>que;//队列
              for(int i=0;i<26;i++)if(ch[0][i])que.push(ch[0][i]),fail[ch[0][i]]=0;//把与根相连的结点push入
              while(!que.empty()){
                  int u=que.front();que.pop();//队列pop
                  for(int i=0;i<26;i++){
                      int v=ch[u][i];
                      if(v)fail[v]=ch[fail[u]][i],que.push(v);//情况1：v存在
                      else ch[u][i]=ch[fail[u]][i];//情况2：v不存在
                  }
              }
          }
          
     	
        
这里还有非常重要的一个细节：若fail[a]=b，则root到a的链一定包含root到b的链。
- 
 查询
 --
 这是一个与KMP最相似的部分。
 
 假设我们要查询s，现在访问到s[i]，s[i]在TRIE树上的编号为now。我们只需定义j=now，然后j不停的fail，期间ans[num[j]]++,答案就出来了。
 
 这些都是基于我刚刚所讲的一个细节。如果root到a的链存在与s，则root到fail[a]的链也存在于s。
 
 这样子的话，所有困难都迎刃而解。
```cpp
void query(string s){
    	int now=0;//当前访问节点
    	for(int i=0;i<s.size();i++){
        	now=ch[now][s[i]-'a'];//更新节点
        	for(int j=now;j;j=fail[j])ans[val[j]]++;//进行答案累计
    	}
	}
```
- 
AC Code
--

	本蒟蒻 8044ms的代码。


        #include<iostream>
        #include<cstdio>
        #include<cstring>
        #include<queue>
        using namespace std;
        string mob[300010];
        int num[300010];
        int ch[300010][26];
        int fail[300010];
        int ans[300010];
        int temp;
        int n,siz;
        void insert(string s,int v){
            int now=0;
            for(int i=0;i<s.size();i++){
                int o=s[i]-'a';
                if(!ch[now][o])ch[now][o]=++siz;
                now=ch[now][o];
            }
            num[now]=v;
        }
        void getfail(){
            int now=0;
            queue<int>que;
            for(int i=0;i<26;i++)if(ch[0][i])que.push(ch[0][i]),fail[ch[0][i]]=0;
            while(!que.empty()){
                int u=que.front();que.pop();
                for(int i=0;i<26;i++){
                    int v=ch[u][i];
                    if(v)fail[v]=ch[fail[u]][i],que.push(v);
                    else ch[u][i]=ch[fail[u]][i];
                }
            }
        }
        void query(string s){
            int now=0;
            for(int i=0;i<s.size();i++){
                now=ch[now][s[i]-'a'];
                for(int j=now;j;j=fail[j])ans[num[j]]++;
            }
        }
        int main(){
            while(cin>>n&&n){
                memset(num,0,sizeof(num));
                memset(ans,0,sizeof(ans));
                memset(ch,0,sizeof(ch));
                memset(fail,0,sizeof(fail));
                siz=0;
                for(int i=1;i<=n;i++){
                    cin>>mob[i];
                    insert(mob[i],i);
                }
                getfail();
                string k;
                cin>>k;
                query(k);
                temp=0;
                for(int i=1;i<=n;i++)if(ans[i]>temp)temp=ans[i];
                cout<<temp<<"\n";
                for(int i=1;i<=n;i++)if(ans[i]==temp)cout<<mob[i]<<"\n";
            }
        }
        
     
     本蒟蒻萌新，不足之处欢迎私信。

---

## 作者：一扶苏一 (赞：48)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10713937.html)

(本文仔细说明了@ FlashHu 大神在upd里的 $O(|S| + |T|)$ 做法，并非简单模板介绍qwq)

## Definition & Solution

AC自动机是一种多模式串的字符串匹配数据结构，核心在于利用 ``fail`` 指针在失配时将节点跳转到当前节点代表字符串的最长后缀子串。

首先对 **模式串** 建出一棵 ``tire`` 树，考虑树上以根节点为一个端点的每条链显然都对应着某一模式串的一个前缀子串，以下以树上的每个节点来代指从根节点到该节点对应的字符串。

定义一个字符串 $S$ 在 ``trie`` 树上“出现过”当且仅当存在一条以根节点为一个端点的链，该链的对应字符串为 $S$。

考虑对每个节点求出一个 ``fail`` 指针，该指针指向在树上出现的该子串的 **最长** 后缀子串的端点。考虑在匹配文本串的时候，如果某一位置失配，最优的选择显然是跳转到被匹配串的最长后缀子串。因为这样所有在树上出现过的字符串都有机会被跳转到。

需要注意的是如果一个字符串匹配到了文本串，那么他的所有后缀子串都能匹配文本串。也就是说对于一个节点，他的fail,fail的fail，一直到根节点都能匹配当前文本串。

考虑求出fail指针的方法：

设根节点为空，显然根节点的所有孩子的fail指着指向根节点。

对于一个已经求出 ``fail`` 指针的节点 $u$，设 $u$ 的 ``fail`` 指向 $w$，考虑 $u$ 的一个孩子 $v$，设 $w$ 对应的孩子为 $z$，且设 $z$ 在 ``trie`` 树上是真实存在的。由于 $w$ 是 $u$ 的最长后缀子串，显然 $w$ 的对应孩子 $z$ 是 $v$ 的最长后缀子串，于是直接将 $v$ 的 ``fail`` 指向 $z$ 即可。考虑如果 $v$ 在 ``fail`` 上是不存在的，那么考虑一个 ``fail`` 指针指向 $u$ 的节点，它对应 $v$ 的指针显然应该指向 $u$ 对应子串加上 $v$ 代表字符后的最长真实存在的后缀子串。显然这个位置是 $z$。为了匹配时方便，我们直接将 $u$ 的子节点指针指向 $z$，这样在匹配 ``fail`` 指针指向 $u$ 的节点时即对应第一种情况，正确性已经得到了证明。

于是一次 BFS 即可解决问题，对于 $u$ 的子节点 $v$ ，如果 $v$ 真是存在，则将 $v$ 的 ``fail`` 指针指向 $u$ 的 ``fail`` 的对应节点，否则将 $v$ 指向 $u$ 的 ``fail`` 的对应子节点。

需要注意的是，如果一个节点再加上一个字符后在树上不存在任何一个后缀子串，那么该最长后缀为空，应该指向根节点。所以在初始化时，应该将所有节点的孩子和 ``fail`` 都指向根节点。

## Samples

### [【P3808】AC自动机（简单版）](https://www.luogu.org/blog/yyc112358/dou-luo-tai-lu-v003-ban)

#### Description

给定 $n$ 个模式串 $S$ 和$1$个文本串 $T$，求有多少个模式串在文本串里出现过。

#### Limitation

模式串总长度和文本串长度都不超过 $10^6$

#### Solution

考虑建出自动机后，在树上按照文本串匹配，注意到每匹配到一个节点，他的所有后缀子串都出现过，于是在每个节点都应该不断跳 ``fail`` 直到根，一路上的子串都标记为出现。

注意到本题只问有多少个串出现，而没有问每个串出现多少次，所以如果一个字符串已经在之前被跳到过了，他的所有后缀子串显然在之前也都已经被跳到过了，所以每跳到一个节点对该节点打一下标记，如果跳到过该节点了就直接break即可。

考虑一个节点最多会被跳一次，一共有 $O(\Sigma|S|)$ 个节点，同时建立自动机的复杂度是 $O(\Sigma|S|)$ 的，另外匹配文本串的复杂度是 $O(|T|)$ 的，于是总时间复杂度 $O(|T| + \Sigma|S|)$

#### Code

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

const int maxt = 26;
const int maxn = 1000009;

struct Tree {
  Tree *son[maxt], *fail;
  int endtime;
  bool vis;

  Tree(Tree *const _rt) : endtime(0), vis(false) {
    for (auto &u : son) u = _rt;
    fail = _rt;
  }

  Tree() : endtime(0), vis(false) {
    fail = this;
    for (auto &u : son) u = this;
  }
};
Tree rot;
Tree *rt = &rot;

int n, ans, pcnt = 0;
char MU[maxn];
std::queue<Tree*>Q;

void makefail();
void ReadStr(char *s);
void query(const char *s);
void insert(const char *s);

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  while (n--) {
    ReadStr(MU); insert(MU);
  }
  makefail();
  ReadStr(MU); query(MU);
  return 0;
}

void ReadStr(char *s) {
  do *s = IPT::GetChar(); while ((*s == ' ') || (*s == '\n') || (*s == '\r'));
  do *(++s) = IPT::GetChar(); while ((~*s) && (*s != ' ') && (*s != '\n') && (*s != '\r'));
  *s = 0;
}

void insert(const char *s) {
  auto u = &rot;
  while (*s) {
    int k = *(s++) - 'a';
    u = u->son[k] != rt? u->son[k] : u->son[k] = new Tree(&rot);
  }
  ++u->endtime;
}

void makefail() {
  for (auto u : rot.son) if (u != rt) {
    Q.push(u);
  }
  while (!Q.empty()) {
    auto u = Q.front(); Q.pop();
    for (auto &v : u->son) {
      auto k = &v - u->son;
      if (v != rt) {
        v->fail = u->fail->son[k];
        Q.push(v);
      } else {
        v = u->fail->son[k];
      }
    }
  }
}

void query(const char *s) {
  auto u = &rot;
  while (*s) {
    u = u->son[*(s++) - 'a'];
    for (auto v = u; v->vis == false; v = v->fail) {
      v->vis = true;
      ans += v->endtime;
    }
  }
  qw(ans, '\n', true);
}
```

### [【P3706】AC自动机（加强版）](https://www.luogu.org/problemnew/show/P3796)

#### Description

给定 $n$ 个模式串 $S$ 和一个文本串 $T$，$S$ 可能在 $T$ 中出现多次，求出现最多的是哪些模式串，出现了多少次。

#### Limitation

$1~\leq~n~\leq~150$

$|S|~\leq~70,~|T|~\leq~10^6$

#### Solution

暴力的想法显然是建出AC自动机然后每匹配到一个节点就暴力跳 ``fail``，考虑本题与上一题的区别在于本题的模式串每出现一次就要统计一次，所以每个节点必须跳 ``fail`` 一直到根。考虑一个字符串 $S$ 的后缀子串个数显然是 $O(|S|)$ 的，匹配文本串的复杂度是 $O(|T|)$ 的，于是总复杂度 $O(|S||T|)$ 的。显然很不优秀。

考虑 AC 自动机的一个神奇性质：将所有的 ``fail`` 指针连成边，构成了一棵树。

##### 证明：

考虑除了根节点以外每个点都有且仅有一个 ``fail`` 指针，根节点没有 ``fail`` 指针，这个条件等价于图上有 $n-1$ 条边。

又由于 ``tire`` 树是联通的，所以该图满足 “联通”，“有 $n-1$ 条边” 两个特性，根据树的判定定理可以证明这是一棵树。QED。

于是考虑跳 ``fail`` 一直到根将路径上的标记+1等价于将某个节点到根的链上所有点的标记整体加一，这个过程显然可以树形DP完成，于是每次在该节点打一个+1的标记即可。每个点的真实标记值为孩子的真是标记值之和加上该节点的标记值。

于是总复杂度 $O(|T|~+~\Sigma|S|)$

#### Code

```cpp
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

const int maxm = 75;
const int maxn = 155;
const int maxt = 26;
const int maxL = 1000005;

struct Tree *rot;

struct Tree {
  Tree *son[maxt], *fail;
  std::vector<int>Endid;
  std::vector<Tree*>tson;
  bool vistag;
  int vistime;

  Tree() {
    for (auto &u : son) u = rot;
    fail = rot;
    vistag = false;
    vistime = 0;
  }

  ~Tree() {
    this->vistag = false;
    for (auto u : son) if (u->vistag) delete u;
  }
};

int n, maxv;
char MU[maxn][maxm], CU[maxL];
std::queue<Tree*>Q;
std::vector<int>ans;

void init();
void work();
void clear();
void print();
void buildfail();
void ReadStr(char *s);
void dfs(Tree *const s);
bool IsLet(const char *const s);
void Inserot(const char *s, const int id);

int main() {
  freopen("1.in", "r", stdin);
  qr(n);
  while (n) {
    clear();
    init();
    buildfail();
    work();
    print();
    n = 0; qr(n);
  }
  return 0;
}

void clear() {
  delete rot;
  maxv = 0; ans.clear();
}

void init() {
  rot = new Tree;
  for (auto &u : rot->son) u = rot;
  rot->fail = rot;
  for (int i = 1; i <= n; ++i) {
    ReadStr(MU[i]);
    Inserot(MU[i], i);
  }
}

void ReadStr(char *s) {
  do *s = IPT::GetChar(); while (!IsLet(s));
  do *(++s) = IPT::GetChar(); while (IsLet(s));
  *s = 0;
}

inline bool IsLet(const char *const s) {
  return (*s >= 'a') && (*s <= 'z');
}

void Inserot(const char *s, const int id) {
  auto u = rot;
  while (*s) {
    int k = *(s++) - 'a';
    u = u->son[k] != rot ? u->son[k] : u->son[k] = new Tree;
  }
  u->Endid.push_back(id);
}

void buildfail() {
  for (auto u : rot->son) if (u != rot) Q.push(u);
  while (!Q.empty()) {
    auto u = Q.front(); Q.pop();
    for (auto &v : u->son) {
      auto k = &v - u->son;
      if (v != rot) {
        v->fail = u->fail->son[k];
        Q.push(v);
      } else {
        v = u->fail->son[k];
      }
    }
  }
  for (auto &u : rot->son) if (u != rot) {
    u->vistag = true; Q.push(u);
  }
  while (!Q.empty()) {
    auto u = Q.front(); Q.pop();
    u->fail->tson.push_back(u);
    for (auto &v : u->son) if ((v != rot) && (v->vistag == false)) {
      v->vistag = true; Q.push(v);
    }
  }
}

void work() {
  ReadStr(CU);
  auto s = CU;
  auto u = rot;
  while (*s) {
    int k = *(s++) - 'a';
    ++((u = u->son[k])->vistime);
  }
  dfs(rot);
}

void dfs(Tree *const u) {
  for (auto v : u->tson) {
    dfs(v);
    u->vistime += v->vistime;
  }
  if (u->Endid.size()) {
    if (u->vistime > maxv) {
      maxv = u->vistime;
      ans.clear();
      for (auto i : u->Endid) ans.push_back(i);
    } else if (u->vistime == maxv) {
      for (auto i : u->Endid) ans.push_back(i);
    }
  }
}

void print() {
  std::sort(ans.begin(), ans.end());
  qw(maxv, '\n', true);
  for (auto i : ans) printf("%s\n", MU[i]);
}
```



---

## 作者：hyfhaha (赞：30)

# 做法：AC自动机

如果没有学过AC自动机，看这里[AC自动机详细讲解](https://www.luogu.org/blog/juruohyfhaha/ac-zi-dong-ji)

无疑，作为模板2，这道题的解法也是十分的经典。

我们先来分析一下题目：输入和模板1一样

1、求出现次数最多的次数

2、求出现次数最多的模式串

明显，我们如果统计出每一个模式串在文本串出现的次数，那么这道题就变得十分简单了，那么问题就变成了如何统计每个模式串出现的次数。

**做法：AC自动机**

首先题目统计的是出现次数最多的字符串，所以有重复的字符串是没有关系的。（因为后面的会覆盖前面的，统计的答案也是一样的）

那么我们就将标记模式串的flag设为当前是第几个模式串。就是下面插入时的变化：

```cpp
trie[u].flag++;
变为
trie[u].flag=num; //num表示该字符串是第num个输入的
```

求Fail指针没有变化，原先怎么求就怎么求。

**查询**：我们开一个数组vis，表示第i个字符串出现的次数。

因为是重复计算，所以不能标记为-1了。

我们每经过一个点，如果有模式串标记，就将vis[模式串标记]++。然后继续跳fail。

这样我们就可以将每个模式串的出现次数统计出来。剩下的大家应该都会QwQ！

### 总代码

```cpp
//AC自动机加强版
#include<bits/stdc++.h>
#define maxn 1000001
using namespace std;
char s[151][maxn],T[maxn];
int n,cnt,vis[maxn],ans;
struct kkk{
	int son[26],fail,flag;
	void clear(){memset(son,0,sizeof(son));fail=flag=0;}
}trie[maxn];
queue<int>q;
void insert(char* s,int num){
	int u=1,len=strlen(s);
	for(int i=0;i<len;i++){
		int v=s[i]-'a';
		if(!trie[u].son[v])trie[u].son[v]=++cnt;
		u=trie[u].son[v];
	}
	trie[u].flag=num;			//变化1：标记为第num个出现的字符串
}
void getFail(){
	for(int i=0;i<26;i++)trie[0].son[i]=1;
	q.push(1);trie[1].fail=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		int Fail=trie[u].fail;
		for(int i=0;i<26;i++){
			int v=trie[u].son[i];
			if(!v){trie[u].son[i]=trie[Fail].son[i];continue;}
			trie[v].fail=trie[Fail].son[i];
			q.push(v);
		}
	}
}
void query(char* s){
	int u=1,len=strlen(s);
	for(int i=0;i<len;i++){
		int v=s[i]-'a';
		int k=trie[u].son[v];
		while(k>1){
			if(trie[k].flag)vis[trie[k].flag]++;	//如果有模式串标记，更新出现次数
			k=trie[k].fail;
		}
		u=trie[u].son[v];
	}
}
void clear(){
	for(int i=0;i<=cnt;i++)trie[i].clear();
	for(int i=1;i<=n;i++)vis[i]=0;
	cnt=1;ans=0;
}
int main(){
	while(1){
		scanf("%d",&n);if(!n)break;
		clear();
		for(int i=1;i<=n;i++){
			scanf("%s",s[i]);
			insert(s[i],i);
		}
		scanf("%s",T);
		getFail();
		query(T);
		for(int i=1;i<=n;i++)ans=max(vis[i],ans);	//最后统计答案
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
		if(vis[i]==ans)
		printf("%s\n",s[i]);
	}
}
```
这样的时间复杂度是多高呢？

O(模式串长度 · 文本串长度)。

想要了解AC自动机的优化，看[**这里**](https://www.luogu.org/blog/juruohyfhaha/ac-zi-dong-ji)

---

## 作者：Taduro (赞：19)

## AC自动机简介

AC自动机是一个用来解决多个字符串匹配的高效算法，传说AC自动机需要掌握trie和kmp，亲测只会trie、完全不懂kmp的傻子也可以理解。

经典应用，判断多个单词是否在一个字符串中出现。

介绍一下它的原理，如果用单纯的trie来解决这个问题，在一个单词匹配完毕的时候，我们会回到trie树的根匹配下一个子串，这就很不优，如果我们能跳到下一个相同字符，并且单词前缀和当前单词后缀相同的位置，就能继续匹配了。

fail指针就是用来完成这个任务的，如果在某节点x匹配字符i失败，我们的指针就要到达t[x].fail处继续匹配，否则就去匹配t[x].ch[i]。

![](https://dftyem.github.io/img/ac1.png)

上一张全网都在用的例图，图中的虚线就是fail指针的指向。

我们发现：fail指针只能指向深度比当前浅的点（退而求其次），如果没有符合要求的点就会指向根（GG）。

fail指针的求法：递推，用bfs先把比一个点深度小的点的fail指针全求出来。对于一个点x，如果它的字符为i，那么我们看看$t[t[x].fa].fail$的儿子中有没有i，有的话就是$t[x].fail=t[t[t[x].fa].fail].ch[i]$ ，否则就一直找下去一直到根。

话是这么说，但是一般写起来不是用暴力模拟我刚刚说的话，而是用一种被dalao称为“补trie图”的做法。

先看代码

```c++
void build(){
	head=tail=1; team[head]=0;
	while (head<=tail){
		int x=team[head];
		for (int i=0; i<26; i++){
			if (x==0){
				if (t[x].ch[i]){
					team[++tail]=t[x].ch[i];
					t[t[x].ch[i]].fail=0;
				}
				continue;
			}
			if (t[x].ch[i]){
				team[++tail]=t[x].ch[i];
				t[t[x].ch[i]].fail=t[t[x].fail].ch[i];
			}
			else t[x].ch[i]=t[t[x].fail].ch[i];
		}
		head++;
	}
}
```

首先，对于根的儿子，他们的fail就是根，入队就完了。

对于其他点，他们的fail就是$t[t[x].fail].ch[i]​$，那么问题来了，要是没有这个点呢？不应该往上跳吗？

不然，看这句：$else\ t[x].ch[i]=t[t[x].fail].ch[i];$ 

如果这个点不存在，那$t[t[x].fail].ch[i]$的值就是$t[t[t[x].fa].fail].ch[i]$

再没有就是$t[t[t[t[x].fa].fa].fail].ch[i]$，祖祖辈辈无穷尽也，一直到根的儿子这个值会是0,0是根的编号。

### fail树

例题 [传送门](https://www.luogu.org/problemnew/show/P3796)

统计每个单词的出现次数，有不少人的写法就是这样（选自某yyb大佬的题解）：

```c++
int l=s.length();
int now=0,ans=0;
for(int i=0;i<l;++i)
{
	now=AC[now].vis[s[i]-'a'];//向下一层
	for(int t=now;t;t=AC[t].fail)//循环求解
		 Ans[AC[t].end].num++;
}
```

但这个会慢是因为每一位都跳到了根，然而没有必要这样做。

以样例为例

![](https://dftyem.github.io/img/ac2.png)

每个点有且只有一个fail指针，而根不算fail指针，将fail指向的点看成自己的爸爸，这样就形成了一棵fail树。

我们暴力统计的时候，每到达一个点是一个单词的末尾，就给这个单词出现次数+1，同时给这个点到根的所有是单词末尾的点都+1。

这样我们只要打好标记，结束后求一遍每个点的子树和，就可以知道他被打了多少次标记了。

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
struct tree{
	int ch[26],cnt,fail;
}t[100001];
struct node{
	int next,to;
}w[150001];
int n,num,pos[200],sum[150001],heap,tail;
int head[150001],team[105001],cnt,maxn;
char ch[200][100],s[1000010];
inline void add(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
}
inline void insert(int x){
	int u=0,l=strlen(ch[x]);
	for (int i=0; i<l; i++){
		int a=ch[x][i]-'a';
		if (!t[u].ch[a]) t[u].ch[a]=++num;
		u=t[u].ch[a];
	}
	t[u].cnt++; pos[x]=u;
}
inline void build(){
	heap=tail=1; team[heap]=0;
	while (heap<=tail){
		int x=team[heap];
		for (int i=0; i<26; i++){
			if (x==0){
				if (t[x].ch[i]){
					t[t[x].ch[i]].fail=0;
					team[++tail]=t[x].ch[i];
				}
				continue;
			}
			if (t[x].ch[i]){
				t[t[x].ch[i]].fail=t[t[x].fail].ch[i];
				team[++tail]=t[x].ch[i];
			}
			else t[x].ch[i]=t[t[x].fail].ch[i];
		}
		heap++;
	}
}
void dfs(int x){
	for (int i=head[x]; i; i=w[i].next){
		dfs(w[i].to); sum[x]+=sum[w[i].to];
	}
}
int main(){
	while (1){
		scanf("%d",&n);
		if (!n) return 0; num=0;
		memset(t,0,sizeof(t));
		memset(ch,0,sizeof(ch));
		memset(pos,0,sizeof(pos));
		memset(sum,0,sizeof(sum));
		memset(head,0,sizeof(head));
		for (int i=1; i<=n; i++){
			scanf("%s",ch[i]);
			insert(i);
		}
		build(); scanf("%s",s); cnt=0;
		for (int i=1; i<=num; i++){
			add(t[i].fail,i);
			// printf("%d %d\n",t[i].fail,i);
		}
		int u=0,l=strlen(s);
		for (int i=0; i<l; i++){
			int a=s[i]-'a';
			u=t[u].ch[a];
			sum[u]++;
		}
		dfs(0); maxn=0;
		for (int i=1; i<=n; i++)
			maxn=max(maxn,sum[pos[i]]);
		printf("%d\n",maxn);
		for (int i=1; i<=n; i++)
			if (sum[pos[i]]==maxn) printf("%s\n",ch[i]);
	}
	return 0;
}
```

---

## 作者：I_AM_HelloWord (赞：17)

还是属于AC自动机的裸题。而AC自动机的裸题，先把模板打好后，基本上改的就是对标记点的处理。

这里就是对AC自动标记点处理的简单修改，即把匹配到的标记点都计数一下，然后求计数最大的那些标记点就行了。

还是不太不懂AC自动记得萌新们可以戳：http://blog.csdn.net/no1\_terminator/article/details/77725530

讲的非常清楚哟！

这里就简单的讲一下吧：

f[u]=v表示从根到u号节点的这个字符串的某个后缀与从根到v号节点的这个字符串是等效的（即完全相等的）

last[u]=v表示从u开始不断沿着失配边跳到的第一个是标记点的端点v，那么我们再匹配是就无需沿着f跳，而是沿着last跳

考虑f的递推。我们设当前节点为u，其一个孩子ch[u][c]=v，k表示u沿着f边跳一次对应的点，即k=f[u],

那么如果u不是根节点，f[v]=ch[k][c]，即沿着k再向下走一个c字符，这时两个字符串还是相等的对不对。

如果u是根节点那就没什么好说的了，f[v]=0。

在此条件下，last就非常好递推了，,那么如果f[v]是标记点，那么last[v]=f[v],

否则last[v]=last[f[v]]。

考虑到这是一个Trie树上的递推，所以我们用BFS搞一搞就好了。

参考代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define reset(a) memset((a),0,sizeof((a)))
#define REP(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;
const int N=1e6+10;
const int M=151*71;
char s[151][71];
char T[N];
int m;
struct Aho_Corasick_Automaton{
    int NodeCnt,f[M],ch[M][26],cnt[M],val[M],last[M];
    void clear(){
        reset(f);reset(ch);reset(cnt);reset(val);reset(last);
        NodeCnt=0;
    }
    void insert(char *s,int index){
        int u=0,n=strlen(s);
        REP(i,0,n-1){
            int c=s[i]-'a';
            if (!ch[u][c])ch[u][c]=++NodeCnt;
            u=ch[u][c];
        }
        val[u]=index;
    }
    void getFail(){
        queue<int> Q;
        Q.push(0);
        while (!Q.empty()){
            int u=Q.front(),k=f[u];Q.pop();
            REP(c,0,25){
                int v=ch[u][c];
                if (!v){ch[u][c]=ch[k][c];continue;}
                f[v]=u?ch[k][c]:0;
                last[v]=val[f[v]]?f[v]:last[f[v]];
                Q.push(v);
            }
        }
    }
    void query(char *T){
        int u=0,n=strlen(T),res=0;
        REP(i,0,n-1){
            int c=T[i]-'a';
            u=ch[u][c];
            if (val[u])cnt[val[u]]++;
            int v=last[u];
            while (v){
                if (val[v])cnt[val[v]]++;
                v=last[v];
            }
        }
        REP(i,1,m)res=max(res,cnt[i]);
        printf("%d\n",res);
        REP(i,1,m)if (cnt[i]==res)printf("%s\n",s[i]);
        return;
    }
}AC;
int main(){
    while (scanf("%d",&m)==1 && m){
        AC.clear();
        REP(i,1,m){
            scanf("%s",s[i]);
            AC.insert(s[i],i);
        }
        AC.getFail();
        scanf("%s",T);
        AC.query(T);
    }
    return 0;
}
```

---

## 作者：空の軌跡 (赞：7)

关于AC自动机的详细过程我就不讲了。关于这道题，我说一下我的操作。因为有些人TLE，还要卡常，我觉得不必要。

### 思路：
AC自动机匹配后，会跳 $fail$ ，这时，我们会重复跳跃到根并对路径上的节点增加贡献。我们发现这样会很浪费时间。

由于 $fail$ 指针构建后将不会改变，这也意味着 一个节点跳 $fail$ 的路径是固定的 。 因此，我们不妨先将贡献加到当前这个节点上，最后再去更新答案。类似于一种 差分数组 的思想。

我是用 $vector$ 保存的，从最深的节点开始计算，可以保证不会出现问题。最后在计算就可以了。

最后时间开了 $O2$ 是 最慢的点 239ms，不开最慢 409ms。反正可以过，时间很宽松。

我的代码直接糊上去了：
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<cstdlib>
#include<vector>
using namespace std;
struct ACTrie
{
    int tree[12000][26],fail[12000],end_[12000],got[12000],dep[12000];
    vector<int>deep[75];
    int root,cnt;
    int newnode()
    {
    	++cnt;
        for(int i=0;i<26;i++)tree[cnt][i]=-1;
		end_[cnt]=got[cnt]=0;
        return cnt;
    }
    void init()
    {
    	for(int i=1;i<72;i++)deep[i].clear();
        cnt=-1;root=newnode();
    }
    int insert_(char str[])
    {
        int len=strlen(str);
        int pos=root;
        for(int i=0;i<len;i++)
        {
            int id=str[i]-'a';
            if(tree[pos][id]==-1)
			{
				tree[pos][id]=newnode();
				dep[tree[pos][id]]=dep[pos]+1;
				deep[dep[pos]+1].push_back(tree[pos][id]);
			}
			pos=tree[pos][id];
        }
        ++end_[pos];
        return pos;
    }
    void build()
    {
        queue<int>que;
        fail[root]=root;
        for(int i=0;i<26;i++)
        {
            if(tree[root][i]==-1)tree[root][i]=root;
            else
            {
                fail[tree[root][i]]=root;
                que.push(tree[root][i]);
            }
        }
        while(!que.empty())
        {
            int now=que.front();
            que.pop();
            for(int i=0;i<26;i++)
            {
                if(tree[now][i]==-1)tree[now][i]=tree[fail[now]][i];
                else
                {
                    fail[tree[now][i]]=tree[fail[now]][i];
                    que.push(tree[now][i]);
                }
            }
        }
    }
    int query(char str[])
    {
        int len=strlen(str);
        int now=root;
        for(int i=0;i<len;i++)
        {
            now=tree[now][str[i]-'a'];
            ++got[now];
        }
        for(int i=72;i>0;i--)
        {
        	for(int j=0;j<deep[i].size();j++)
        	{
        		int x=deep[i][j];
        		got[fail[x]]+=got[x];
			}
		}
		int gotmax=0;
		for(int i=1;i<=cnt;i++)
		if(end_[i])gotmax=max(gotmax,got[i]);
		return gotmax;
    }
};
char str[160][77];
char niubi[1000010];
int totrie[160];
ACTrie ac;
int main()
{
	ios::sync_with_stdio(0);
    int n;cin>>n;
    while(n)
	{
		ac.init();
	    for(int i=1;i<=n;i++)
	    {
	    	cin>>str[i];
	        totrie[i]=ac.insert_(str[i]);
	    }
	    ac.build();cin>>niubi;
	    int gotmax=ac.query(niubi);
	    cout<<gotmax<<'\n';
	    for(int i=1;i<=n;i++)
	    if(ac.got[totrie[i]]==gotmax)cout<<str[i]<<'\n';
	    cin>>n;
	}
}
```

---

## 作者：zhuixun_ (赞：5)

不会AC自动机，但不妨碍做本题，

水题,trie树暴力匹配过~

注意输出结果时要按照输入的顺序排序。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int tot=0;
const int N=150*70+10;
int ch[N][26],vis[N],mark[(int)(1e6+10)];

struct node{
	string str;
	int num;//统计每个模板串出现次数
	int appear;//记录每个模板串出现的时间
	bool operator <(const node &b){
		if(num==b.num) return appear<b.appear;
		return num>b.num;
	}
	
	void init(){
		num=0;
		str="";
	}
}mp[N];

void add(string str,int appear){
	int u=0;
	for(int i=0;i<str.size();i++){
		int id=str[i]-'a';
		if(!ch[u][id]) ch[u][id]=++tot;
		u=ch[u][id];
	}
	vis[u]=1;
	mp[u].str=str;
	mp[u].appear=appear;
}

void check(string str){
	for(int k=0;k<str.size();k++){
		int u=0;
		for(int i=k;i<str.size();i++){
			int id=str[i]-'a';
			if(ch[u][id]) u=ch[u][id];
			else break;
			
			if(vis[u]) mp[u].num++;
		}
	}
}
int main(){
	freopen("p.txt","r",stdin);
	while(scanf("%d",&n)&&n){
		memset(vis,0,sizeof(vis));
		memset(ch,0,sizeof(ch));
		for(int i=0;i<N;i++) mp[i].init();
		tot=0;

		for(int i=0;i<n;i++){
			string str;
			cin>>str;
			add(str,i);
		}
		
		string T;
		cin>>T;
		check(T);
		
		sort(mp,mp+N);
		int pos=mp[0].num;
		printf("%d\n",pos);
		for(int i=0;i<N;i++){
			if(mp[i].num==pos) cout<<mp[i].str<<"\n";
			else break;
		}
	}
	return 0;
}
```

---

## 作者：CodyTheWolf (赞：4)

### [开头小广告：自己做的一个模板库OwO](https://www.luogu.org/blog/29354/Templet)

------------
## 在这里HACK几乎所有的题解（因为好像没发现有对的？

```
4
AB
BC
CD
ABCD
ABCD
0
```

### 答案应该是

```
1
AB
BC
CD
ABCD

```
## 而其他同学都只输出了个别答案？？

### 例如

```
1
AB
ABCD

```

### 或

```
1
AB
BC
CD

```

------------
### 会出现上面的情况，只是因为没有判断串包含的关系或者是直接退回重新匹配了
 嗷？什么意思？？
## 举例：
>*  当匹配完串$AB$时：
>*  如果写的自动机不退回到B并且重新匹配（从trie树的树根开始），而是继续匹配，那么会忽略掉$BC$,$CD$两个答案，所以最终只会输出$AB$和$ABCD$这两个答案
>*  如果写的自动机退回到B重新匹配（从trie树的树根开始），那么$AB$,$BC$,$CD$都会匹配到，但是因为退回的关系，ABCD并没有被匹配到，这和上面的问题貌似有点矛盾了。
### 上面的问题只是我自己遇到的，可能还会有其他情况，但是鉴于大多数题解并没有输出正确答案，这里给出一个我自己的解决方法：
>*  其实罪魁祸首只是**退回重新匹配的时候，没有匹配到最后重新匹配了**，就像匹配AB时不继续往下匹配ABCD，而是跳回根匹配B。很显然我们只要让自动机匹配到最深节点，再往回跳就对了。
>*  有的自动机直接把最深的节点下没有的节点指向了最深节点的fail
>*  可能这行代码长这样：$trie[x][i] = trie[fail[x]][i];$
>*  这就是我们的判断依据了，如果下一个匹配字符是跳到fail的下面的话，说明下面已经没有节点，只是我们优化连了节点而已，这个时候就可以退回trie的根重新匹配了
>* ### 即当$trie[x][c[i+1] - 'a'] == trie[fail[x]][c[i+1] - 'a']$时
注：c[i+1]是下一个匹配字符


------------
### 最后，可能这个不是唯一解决的办法，或者说会有更好AC自动机写法可以避免这个问题。这篇题解的来源是我自己打模拟赛写的自动机跑不过像这样的例子，而我自己在luogu上打的模板却AC了，于是把题解都跑了一下发现都不太正确，在此纠正一下（也有可能是自己太傻XD）
------------
# CODE
有些地方有小注释
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1e6 + 5, MAXA = 26;
const int MAXP = 155, MAXLEN = 75;

int n;

queue<int> Q;

struct Automaton
{
    char p[MAXP][MAXLEN];

    int trie[MAXN][MAXA], fail[MAXN];
    int num[MAXN], nxt[MAXN], tot;

    signed id[MAXN][1], tail[MAXN];

    bool tag[MAXN];

    const int root = 0;

    inline void Memset(void)
    {
        memset(trie, 0, sizeof trie);
        memset(fail, 0, sizeof fail);
        memset(num, 0, sizeof num);
        memset(tag, 0, sizeof tag);
        memset(tail, 0, sizeof tail);

        return;
    }

    inline void Insert(int rak)
    {
        char *c = p[rak];
        int x = root, len = strlen(c);

        for (int i = 0; i < len; i++)
        {
            if (!trie[x][c[i] - 'a'])
                trie[x][c[i] - 'a'] = ++tot;
            x = trie[x][c[i] - 'a'];
        }
        tag[x] = true, nxt[x] = len - 1, id[x][++tail[x]] = rak;//nxt是长度-1，也是匹配到这个位置应该退回多少个字符

        return;
    }

    inline void MakeFail(void)
    {
        for (int i = 0; i < MAXA; i++)
            if (trie[root][i])
                Q.push(trie[root][i]);

        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();

            for (int i = 0; i < MAXA; i++)
            {
                if (trie[x][i])
                {
                    fail[trie[x][i]] = trie[fail[x]][i];//这里是上面讲的优化
                    Q.push(trie[x][i]);
                }
                else
                    trie[x][i] = trie[fail[x]][i];//可以依据这个判断后面是否还有节点，解决本题解讨论的问题
            }
        }

        return;
    }

    inline void Compare(char *c)
    {
        int ans = 0, x = root;

        for (int i = 0, len = strlen(c); i < len; i++)
        {
            x = trie[x][c[i] - 'a'];

            if (tag[x])
            {
                for (int j = 1; j <= tail[x]; j++)
                    ans = max(ans, ++num[id[x][j]]);

                if (trie[x][c[i+1] - 'a'] == trie[fail[x]][c[i+1] - 'a'])//题解的核心！
                    i -= nxt[x], x = root;
            }
        }

        printf("%d\n", ans);
        for (int i = 1; i <= n; i++)
            if (num[i] == ans)
                printf("%s\n", p[i]);
    }

} AC;

char s[MAXN];

signed main(void)
{
    scanf("%d", &n);
    while (n)
    {
        AC.Memset();

        for (int i = 1; i <= n; i++)
            scanf("%s", AC.p[i]), AC.Insert(i);
        AC.MakeFail();

        scanf("%s", s);
        AC.Compare(s);

        scanf("%d", &n);
    }

    return 0;
}

```


---

## 作者：晚安晚安 (赞：2)

## ac自动机裸题

虽说是加强版,不过其实就是稍微换了下求的东西,还是很裸的

具体改动的地方在代码里给出

上菜:

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 300000+5;
const int SIGMA_SIZE = 26;
int maxx = 0;//得出的最大大数目答案
char p[200][105];//用来输出字符答案
int ans[200];//唯一加的地方,用来存答案
char T[1000000+5];
queue <int> qe;
//ac自动机 机体qvq ps:感觉这种自动机写起来最好看(雾
struct AC_automata
{
    int ch[maxn][26], val[maxn], f[maxn], cnt = 0;
    void clear()//给数组清零
    {
        cnt = maxx = 0;
        for(int i = 0; i < maxn; ++i)
        {
            val[i] = f[i] = 0;
            for(int j = 0; j < 26; ++j)ch[i][j] = 0;
        }
        memset(ans, 0, sizeof ans);
    }
    void insert(char *s, int num)
    {
        int now = 0;
        for(int i = 0; i < strlen(s); i++)
        {
            if(!ch[now][s[i]-'a'])ch[now][s[i]-'a'] = ++cnt;
            now = ch[now][s[i]-'a'];
        }
        val[now] = num;
    }
    void getFail()
    {
        for(int i = 0; i < SIGMA_SIZE; i++)if(ch[0][i])qe.push(ch[0][i]);
        while(!qe.empty())
        {
            int u = qe.front();qe.pop();
            for(int i = 0; i < SIGMA_SIZE; i++)
            {
                if(ch[u][i]){f[ch[u][i]] = ch[f[u]][i];qe.push(ch[u][i]);}
                else ch[u][i] = ch[f[u]][i];
            }
        }
    }
    void find()
    {
        int len = strlen(T), now = 0;
        for(int i = 0; i < len; i++)
        {
            now = ch[now][T[i]-'a'];
            for(int t = now; t; t = f[t]){if(val[t]){ans[val[t]]++;if(t!=0)maxx = max(maxx,ans[val[t]]);}}
        }
    }
}AC;
int n;
int main()
{
    while(scanf("%d", &n) == 1 && n)
    {
        AC.clear();
        for(int i = 1; i <= n; ++i)
            scanf(" %s", p[i]),AC.insert(p[i], i);
        AC.getFail();
        scanf("%s", T);
        AC.find();
        printf("%d\n", maxx);
        for(int i = 1; i <= n; ++i)if(ans[i] == maxx)printf("%s\n", p[i]);
        //如果找到和答案一样数目的单词就输出
    }
    return 0;
}
```

---

## 作者：Accoty_AM (赞：1)

## 这篇题解主要说一下如何找出现次数
因为这道题没有说是否有重复子串，所以可能一个节点里有多个相同子串。~~虽然字串可能是唯一的，但也算是一种思路扩展吧。~~

如果只是单纯标记一个节点看这组数据

2

aba

aba

ababa

0

就会输出 2 aba

然而我们要 2 aba aba，这就需要特殊处理。。。

于是我们每个节点开一个vector
```cpp
vector<int> sum[100000];
```
在处理到结尾的时候加入vector
```cpp
void insert(char *s,int st){
	int len=strlen(s);
	int p=0;
	for(int c,k=0;k<len;++k){
		c=s[k]-'a';
		if(!trie[p][c]) trie[p][c]=++tot;
		p=trie[p][c];
	}
	sum[p].push_back(st);//这里加入
}
```
在计数的时候加上vector里的值
```cpp
void ask(char *s){
	int len=strlen(s);
	int p=0;
	can[0]=-1;
	for(int k=0;k<len;++k){
		p=trie[p][s[k]-'a'];
		for(int i=p;i&&can[i]!=-1;i=fail[i]){
			for(vector<int>::iterator it=sum[i].begin();it!=sum[i].end();++it)
				++total[*it].val;//这里计数
		}
	}
}
```

完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
inline int read(){
	rg char ch=getchar();
	rg int x=0,f=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
int trie[100000][26],tot,mode[100000],fail[100000];
char have[155][75];
char s[1000010];
int n,r,l;
struct node{
	int id,val;
}total[155];
void insert(char *s,int st){
	int len=strlen(s);
	int p=0;
	for(int c,k=0;k<len;++k){
		c=s[k]-'a';
		if(!trie[p][c]) trie[p][c]=++tot;
		p=trie[p][c];
	}
	mode[p]=st;
}
void clear(){
	for(int i=0;i<=tot;++i)//这里防止tot很小一个一个加。
		for(int j=0;j<26;++j)
			trie[i][j]=0;
	for(int i=0;i<=tot;++i) fail[i]=0;
	memset(mode,0,sizeof mode);
	tot=0;
}
void getf(){
	queue<int> q;
	for(int i=0;i<26;++i)
		if(trie[0][i]) q.push(trie[0][i]);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<26;++i){
			if(trie[x][i]){
				fail[trie[x][i]]=trie[fail[x]][i];
				q.push(trie[x][i]);
			}else trie[x][i]=trie[fail[x]][i];
		}
	}
}
void ask(char *s){
	int len=strlen(s);
	int p=0;
	for(int k=0;k<len;++k){
		p=trie[p][s[k]-'a'];
		for(int i=p;i;i=fail[i]){
			++total[mode[i]].val;
		}
	}
}
bool cmp(const node &a,const node &b){
	if(a.val==b.val) return a.id<b.id;
	return a.val<b.val;
}
int main(){
	cin>>n;
	while(n){
		clear();
		for(int i=1;i<=n;++i) scanf("%s",have[i]),insert(have[i],i),total[i].id=i,total[i].val=0;
		getf();
		scanf("%s",s);
		ask(s);
		sort(total+1,total+1+n,cmp);
		r=l=n;
		while(total[l].val==total[l-1].val) --l;
		printf("%d\n",total[n].val);
		for(int i=l;i<=r;++i) printf("%s\n",have[total[i].id]);
		cin>>n;
	}
	return 0;
}
```
time（O2）1476

---

## 作者：Cekavis (赞：1)

可能会是第一个题解...也只是来水一发


鉴于我水平太差,也没有完全理解这算法.甚至自己的程序~~(搬运了其他题)~~


~~各类资料应该也很多,丑陋的代码仅作为参考~~


```cpp
#include<iostream>
#include<string.h> 
using namespace std;
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
const int MC=26;

struct T{//trie的一个结点吧..
  T *Pre[MC],*F;
  int Num;
  T(){memset(Pre,0,sizeof Pre),F=0,Num=0;}
}*R;

void I(char s[],int k){//插入一个模式串
  T *p=R;
  for(int i=0;s[i];i++){
    if(p->Pre[s[i]-'a']==0) p->Pre[s[i]-'a']=new T();
    p=p->Pre[s[i]-'a'];
  }
  p->Num=k;//仅仅记录该节点表示的模式串,如有重复模式串,应该会有问题
}

T *q[600005];

void Build(){//构造DFA
  int t=0;
  R->F=R;
  rep(j,0,MC-1) if(R->Pre[j]==0) R->Pre[j]=R;
    else{
      q[++t]=R->Pre[j];
      q[t]->F=R;
    }
  rep(cur,1,t){
    T *i=q[cur];
    rep(j,0,MC-1) if(i->Pre[j]!=0){
      T *k=i->F;
      while(k->Pre[j]==0) k=k->F;
      k=k->Pre[j];
      q[++t]=i->Pre[j];
      q[t]->F=k;
    }
  }
}

int n,ans,f[152];
char s[1000005],t[152][72];

int main(){
  cin>>n;
  while(n){
    R=new T();
    rep(i,1,n) scanf("%s",&t[i]),I(t[i],i);//插入模式串
    Build();
    scanf("%s",&s);
    T *cur=R;
    ans=0;
    for(int i=0;s[i];i++){
      int k=s[i]-'a';
      while(cur->Pre[k]==0) cur=cur->F;
      cur=cur->Pre[k];
      for(T *tmp=cur;1;tmp=tmp->F){
        ++f[tmp->Num];//            f[i]表示第i个模式串出现次数
        if(tmp==tmp->F) break;
      }
    }
    rep(i,1,n) ans=max(ans,f[i]);
    printf("%d\n",ans);
    rep(i,1,n) if(f[i]==ans) printf("%s\n",t[i]);
    cin>>n;
    memset(f,0,sizeof f);
  }
  return 0;
}
```

---

## 作者：RicardoShips (赞：0)

~~明天放假，今天没什么心思做题，就来水一篇题解~~

~~其实也是顺便做一个字符串的小结~~

前置技能

- $Trie$字典树

- $KMP$

~~以下内容绝大多数来自百度百科~~

$Trie$树，是一种树形结构，是一种哈希树的变种

典型应用是用于统计，排序和保存大量的字符串

~~感觉说了等于没说~~

简言之，就是把要匹配的字符串变成树形结构再去匹配

$KMP$算法是一种先进的字符串匹配算法

$KMP$算法的关键是利用匹配失败后的信息

尽量减少模式串与主串的匹配次数以达到快速匹配的目的

具体实现就是实现一个$next$函数，函数本身包含了模式串的局部匹配信息

这个$next$函数学名叫失配函数，~~就是匹配失败的时候使用的~~

建立一个$AC$自动机通常需要两个步骤

- 构建$Trie$树

- 对$Trie$树上所有的结点构造失配指针

~~废话讲完了，下面的才是重点~~

**如何构造失配指针？？？**

构建$fail$指针，可以参考$KMP$中构造$next$数组的思想

我们可以考虑用线性递推的方法来构建

具体的操作类似一个$BFS$，构建一个优先队列

然后一层一层去扩展，标记$fail$指针

这里要按照节点是否存在的情况讨论一下，推荐手玩几组样例

代码其实很短，但是理解起来真的很难

[安利一个带$GIF$的博客](https://www.luogu.org/blog/42196/qiang-shi-tu-xie-ac-zi-dong-ji)，~~其实是我讲不清~~

构造之后再回到母串中逐个匹配

用$fail$指针自动跳转到下一个位置

取反是用来判断是否那个点已经经过

这里感觉很像跑图论，其实也就是在跑字典图

~~好像$AC$自动机就这么一点点？？？~~

引用某大神一句话，强行总结一句$AC$自动机的运行原理

**构建字典图实现自动跳转，构建失配指针实现多模式匹配**

因为我代码常数很大，所以实用价值不高，~~但是还是贴一下~~

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[155][75];
char T[1000001];
int sum[1000001];
int val[1000001];
int fail[1000001];
int son[1000001][27];
int ans,mmp,tot,root,N;
inline void insert(char *s,int I)
{
    int M=strlen(s+1),now=root;
    for(register int i=1;i<=M;++i)
    {
        int x=s[i]-'a';
        if(!son[now][x]) son[now][x]=++tot;
        now=son[now][x];
    }
    val[now]=I;
}
inline void miss()
{
    queue < int > Q;
    for(register int i=0;i<26;++i)
        if(son[root][i]) Q.push(son[root][i]);
    while(!Q.empty())
    {
        int p=Q.front();Q.pop();
        for(register int i=0;i<26;++i)
            if(!son[p][i]) son[p][i]=son[fail[p]][i];
            else fail[son[p][i]]=son[fail[p]][i],Q.push(son[p][i]);
    }
}
int main()
{
    while(scanf("%d",&N)&&N)
    {
        memset(s,0,sizeof(s));memset(son,0,sizeof(son));memset(sum,0,sizeof(sum));
        memset(val,0,sizeof(val));memset(fail,0,sizeof(fail));
        for(register int i=1;i<=N;++i) scanf("%s",s[i]+1),insert(s[i],i);
        miss();ans=0;scanf("%s",T+1);int M=strlen(T+1),now=root;
        for(register int i=1;i<=M;++i)
        {
            now=son[now][T[i]-'a'];
            for(register int j=now;j;j=fail[j]) if(val[j]) ++sum[val[j]];
        }
        for(register int i=1;i<=N;++i) ans=max(ans,sum[i]);
        printf("%d\n",ans);
        for(register int i=1;i<=N;++i)
            if(ans==sum[i]) printf("%s\n",s[i]+1);
    }
    return 0;
}
```

---

## 作者：ww3113306 (赞：0)

貌似跑得还不是很慢？

不过一开始没按输入顺序输入一片wa。。。/(ㄒoㄒ)/~~

其实乍一看还挺难的，

然而想一下发现并不难

建议先做简单版再来

这里相对简单版只要改几个地方就可以了

首先我们增加一个father数组记录father，一个a数组记录每个节点存的是哪个字符，以便输出

然后将ans变为一个结构体

num的作用是判断顺序以及记录节点位置

在匹配文本串的时候，每匹配到一个，就把对应节点的ans.date++，

同时注意val不能清零，因为要支持一个串多次出现。

由于我们是按顺序插入模式串，所以每个模式串的结尾对应的节点的下标是单调上升的，因此num小即代表输入顺序靠前
因此在最后统计答案的时候按照date为第一关键字，num为第二关键字排序，并输出即可

由于ans是直接统计在结尾节点对应下标上的，
所以直接就得到了对应串的结尾位置在哪，
然后增加一个数组，（为了实现正序输出）
因为从下面跑到上面的话，访问的次序其实是倒的，如果直接输出就会把模式串倒过来，因此开一个数组记录即可。
注意每次都要初始化

	#include<bits/stdc++.h>
	using namespace std;
	#define maxn 10510
	#define R register int
	int n;char s[1000005];
	int q[1000005],head,tail;
	int father[maxn],a[maxn];
	int c[maxn][26],val[maxn],fail[maxn],tot;
	char out[80];

	struct abc{
		int date,num;
	}ans[maxn];
	
	struct Aho_Corasick_Automaton
	{
		void add()//加入trie树
		{
			int len=strlen(s),now=0;
			for(R i=0;i<len;i++)
			{
				int v=s[i]-'a';//记录是哪个个字母
				if(!c[now][v])	c[now][v]=++tot,father[tot]=now,a[tot]=v;
				now=c[now][v];
			}
			val[now]++;
		}
	
		void build()
		{
			R now;
			head=tail=0;
			for(R i=0;i<26;i++)
				if(c[0][i]) fail[c[0][i]]=0,q[++tail]=c[0][i];
			while(head<tail)
			{
				now=q[++head];
				for(R i=0;i<26;i++)
					if(c[now][i]) fail[c[now][i]]=c[fail[now]][i],q[++tail]=c[now][i];
					else c[now][i]=c[fail[now]][i];//如果father的最长公共前缀的下一个刚好可以匹配的话，就直接把fail指过去就可以了
			}
		}
	
		void search()
		{
			int len=strlen(s),now=0;
			for(R i=0;i<len;i++)
			{
				now=c[now][s[i]-'a'];
				for(R t=now; t && ~val[t] ;t=fail[t]) ans[t].date+=val[t];
			}
		}
	}AC;

	bool cmp(abc a,abc b)
	{
		if(a.date!=b.date) return a.date>b.date;
		if(a.num!=b.num) return a.num<b.num;//error!!!因为输出要按输入顺序
	}

	void work()
	{
		R now,cnt=0;
	
		while(1)
		{
			scanf("%d",&n);
			if(!n)return ;
			tot=0;
			memset(c,0,sizeof(c));
			for(R i=1;i<=maxn;i++)ans[i].date=0;
			memset(val,0,sizeof(val));
			for(R i=1;i<=maxn;i++)	ans[i].num=i;//由于每次sort后都会打乱num的次序，所以与其再sort一次，不如扫一遍重新赋值
		
			for(R i=1;i<=n;i++)	scanf("%s",s),AC.add();
			AC.build();
			scanf("%s",s);
			AC.search();
			sort(ans+1,ans+maxn,cmp);
			printf("%d\n",ans[1].date);
			now=ans[1].num;
			cnt=0;
			while(now)
			{
				out[++cnt]=a[now]+'a';
				now=father[now];
			}
			for(R i=cnt;i>=1;i--) printf("%c",out[i]);
			printf("\n");
			for(R i=2;i<=n;i++)
			{
				if(ans[i].date!=ans[i-1].date)	break;
				now=ans[i].num;
				cnt=0;
				while(now)
				{
					out[++cnt]=a[now]+'a';
					now=father[now];
				}
				for(R i=cnt;i>=1;i--) printf("%c",out[i]);
				printf("\n");
			}
		}
	}

	int main()
	{
		freopen("in.in","r",stdin);
		work();
		fclose(stdin);
		return 0;
	}

---

## 作者：_Chris° (赞：0)

一道模板题，~~然而我搞了1小时~~，~~可能是我还是太菜了~~~~

如果你还不知道AC自动机是什么那就[]()

这个比简单版稍微有所改动，那么这里我们就用一个ans数组存一下答案
因为我们要求解出现的次数，于是就不用标记了，在失配时只需要判断j是否为
0就可以了，如果是一个单词的末尾（也就是cnt>0）就用ans记一下就OK了。

其他的话基本一样，不过还有一点！就是排序时要按输入顺序来，不然只有20分，
~~我就是在这卡了好久~~。```

Code
```
#include<bits/stdc++.h>
#define N 160
using namespace std;
struct node{
	int fail,cnt;
	int next[26];
}AC[N*100];
struct no{
	int id,num;
}ans[N*100];
int n,k=0,tot=0;
char a[N][N],text[N*N*N];
void build(int id,char *s,int now){
	int len=strlen(s);
	for(int i=0;i<len;i++){
		int j=s[i]-'a';
		if(AC[id].next[j]==0) AC[id].next[j]=++k;
		id=AC[id].next[j];
	}
	AC[id].cnt=now;ans[now].id=now;
}
void match(int id){
	queue<int> q;
	for(int i=0;i<26;i++){
		if(AC[id].next[i]==0) continue;
		AC[AC[id].next[i]].fail=id;
		q.push(AC[id].next[i]);
	}
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(AC[now].next[i]==0){
				AC[now].next[i]=AC[AC[now].fail].next[i];
				continue;
			}
			AC[AC[now].next[i]].fail=AC[AC[now].fail].next[i];
			q.push(AC[now].next[i]);
		}
	}
}
void sovel(int id,char *s){
	int len=strlen(s);
	for(int i=0;i<len;i++){
		int j=AC[id].next[s[i]-'a'];
		while(j!=0){
			if(AC[j].cnt>0) ans[AC[j].cnt].num++;
			j=AC[j].fail;
		}
		id=AC[id].next[s[i]-'a'];
	}
}
bool cmp(no a,no b){
	if(a.num==b.num) return a.id<b.id;
	return a.num>b.num;
}
int main()
{
	while(1){
		k=0;tot=0;
		memset(&AC,0,sizeof(AC));memset(&ans,0,sizeof(ans));
		scanf("%d",&n);
		if(n==0) break;
		for(int i=1;i<=n;i++) {scanf(" %s",a[i]),build(0,a[i],i);}
		match(0);
		scanf(" %s",text);
		sovel(0,text);
		sort(ans+1,ans+n+1,cmp);
		printf("%d\n%s\n",ans[1].num,a[ans[1].id]);
		for(int i=2;i<=n;i++){
			if(ans[i].num!=ans[i-1].num) break;
			printf("%s\n",a[ans[i].id]);
		}
	}
	return 0;
} 

---

