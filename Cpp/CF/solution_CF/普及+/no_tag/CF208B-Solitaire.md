# Solitaire

## 题目描述

A boy named Vasya wants to play an old Russian solitaire called "Accordion". In this solitaire, the player must observe the following rules:

- A deck of $ n $ cards is carefully shuffled, then all $ n $ cards are put on the table in a line from left to right;
- Before each move the table has several piles of cards lying in a line (initially there are $ n $ piles, each pile has one card). Let's number the piles from left to right, from 1 to $ x $ . During one move, a player can take the whole pile with the maximum number $ x $ (that is the rightmost of remaining) and put it on the top of pile $ x-1 $ (if it exists) or on the top of pile $ x-3 $ (if it exists). The player can put one pile on top of another one only if the piles' top cards have the same suits or values. Please note that if pile $ x $ goes on top of pile $ y $ , then the top card of pile $ x $ becomes the top card of the resulting pile. Also note that each move decreases the total number of piles by 1;
- The solitaire is considered completed if all cards are in the same pile.

Vasya has already shuffled the cards and put them on the table, help him understand whether completing this solitaire is possible or not.

## 说明/提示

In the first sample you can act like that:

- put the 4-th pile on the 1-st one;
- put the 3-rd pile on the 2-nd one;
- put the 2-nd pile on the 1-st one.

In the second sample there is no way to complete the solitaire.

## 样例 #1

### 输入

```
4
2S 2S 2C 2C
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
3S 2C
```

### 输出

```
NO
```

# 题解

## 作者：EnochWenzhou (赞：6)

考虑使用记忆化搜索。每一个状态记录4个值，目前的长度len以及倒数三张牌a,b,c是哪三张即dfs(len,a,b,c)。那么转移方式有两种：假如c能堆到倒数第2堆上就dfs(len-1,len-3,a,c),假如c能堆到倒数第四张上就dfs（len-1,c,a,b）,容易推得。如果直接搜索很明显2^50会炸掉，因此需要以f[len][a][b][c]记录目前这个状态是否是不能成功的。

AC：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define rint register int
using namespace std;bool f1;
int n,f[55][55][55][55];
char s[110][3];
bool dfs(int l,int a,int b,int c){
	if(l==1)return 1;//长度为1则已经堆完了
	if(f[l][a][b][c])return 0;//已知不能成功就不再判断
	if(s[c][0]==s[b][0]||s[c][1]==s[b][1])if(dfs(l-1,l-3,a,c))return 1;//倒数第二堆的情况
	if(l>3&&s[c][0]==s[l-3][0]||s[c][1]==s[l-3][1])if(dfs(l-1,c,a,b))return 1;//倒数第四张的情况
	f[l][a][b][c]=1;//不能成功则标记
	return 0;
}
bool f2;int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%s",&s[i]);
	if(dfs(n,n-2,n-1,n))puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：dbodb (赞：2)

设$dp[n][i][j][k];$表示长度为n，第n-2个的状态为i，第n-1个的状态为j，第n个的状态为k，能不能成功操作。

```c++
#include<bits/stdc++.h>
#define INF 1000000
using namespace std;
char s1[15]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
char s2[5]={'S','D','H','C'};
int dp[60][60][60][60];
int a[60];
int pan(int x,int y)
{
    if(x%4==y%4)return 1;
    if(x/4==y/4)return 1;
    return 0;
}
int dfs(int ns,int x,int y,int z)
{
    if(dp[ns][x][y][z]!=-1)return dp[ns][x][y][z];
    if(ns<=3)
    {
        if(pan(x,z)&&pan(y,z))
        {
            dp[ns][x][y][z]=1;
        }
        else dp[ns][x][y][z]=0;
        return dp[ns][x][y][z];
    }
    int leap=0;
    if(pan(y,z)&&dfs(ns-1,a[ns-3],x,z))
        leap=1;
    if(pan(a[ns-3],z)&&dfs(ns-1,z,x,y))
        leap=1;
    dp[ns][x][y][z]=leap;
    return leap;
}
int main()
{
    int n,m,i,j,k;
    char str[11];
    while(~scanf("%d",&n))
    {
        memset(dp,-1,sizeof(dp));
        for(i=1;i<=n;i++)
        {
            scanf("%s",str);
            for(j=0;j<13;j++)
                if(str[0]==s1[j])a[i]=j;
            for(j=0;j<4;j++)
                if(str[1]==s2[j])a[i]=a[i]*4+j;
        }
        if(n<3)
        {
            if(n==1)cout<<"YES"<<endl;
            if(n==2)
            {
                if(pan(a[1],a[2]))cout<<"YES"<<endl;
                else cout<<"NO"<<endl;
            }
        }
        else
        {
            if(dfs(n,a[n-2],a[n-1],a[n]))cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;
}

```



---

## 作者：lmy_2011 (赞：0)

### 整体思路
此题的花色与点数总共只有 $19$ 种，显而易见，这题是个裸的深度优先搜索，再与模拟进行配合。

搜索的时候需要记录失败的状态，这里的状态保存只保存当长度一定时后 $3$ 位的状态，因为只有后 $3$ 位状态会出现不同。
### 代码
更多思路我们牵至代码内讲：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[55][5];
int book[55][55][55][55];
int dfs(int l,int s1,int s2,int s3){//l是当前的长度，s1s2s3是后三位
   if(l==1) 
       return 1;//如果已经是一摊牌，就成功了
   if(book[l][s1][s2][s3]==1) 
       return 0;//如果这个状态已经标记过了，就不要走了，肯定走不通
   if(s[s2][0]==s[s3][0] || s[s2][1]==s[s3][1])//比较n和n-1的花色和数字
    if(dfs(l-1,l-3,s1,s3)) 
        return 1;//下个状态长度是l-1,下个状态的后三位 s3把s2覆盖掉
    if(l>=4 && s[s3][0]==s[l-3][0] || s[s3][1]==s[l-3][1])
        if(dfs(l-1,s3,s1,s2)) 
            return 1;//下个状态长度是l-1,下个状态的后三位 s3把l-3覆盖掉
    book[l][s1][s2][s3]=1;//标记走过的状态
    return 0;
}
int main(){
    int n;
    while(scanf("%d",&n)!=EOF){
        memset(book,0,sizeof(book));
        for(int i=1;i<=n;i++) 
            scanf("%s",s[i]);
        if(dfs(n,n-2,n-1,n)==1) 
            printf("YES\n");
        else 
            printf("NO\n");
 
    }
    return 0;
}
```


---

