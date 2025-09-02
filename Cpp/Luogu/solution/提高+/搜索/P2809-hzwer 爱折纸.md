# hzwer 爱折纸

## 题目描述

hzwer 买到了一张神奇的小纸条，初始时它由 $N$ 个格子组成，每个格子上面有一个整数 $N_i$，显然每两个相邻的格子之间有一条分界线，hzwer 可以选择任意一条分界线，将整张纸条进行向左翻折，如果翻折后有两个格子重叠，那么翻折后的格子上数字为原两个格子数字之和，否则数字保持不变。hzwer 也可以将整张纸条进行向左翻转，翻转之后第 $i$ 个格子的数字变成第 $N - i + 1$ 个格子的数字。

![](https://cdn.luogu.com.cn/upload/pic/2350.png)

![](https://cdn.luogu.com.cn/upload/pic/2351.png)


## 说明/提示

对于 $70 \%$ 的数据，$N \le 10$。  
对于 $100 \%$ 的数据，$1 \le N \le 15$。

## 样例 #1

### 输入

```
7
5 6 23 8 19 7 10
4
5 16 30 27
7
1 2 3 4 5 6 7
5
7 6 5 5 5
4
1 2 3 4
1
10
6
19 23 3 51 2 0
2
34 64```

### 输出

```
S
S
S
N```

# 题解

## 作者：Yy666_l (赞：6)

# 居然没c++题解
## 其实这题暴力枚举再用一个什么东西判个重就行了
~~其实是想不到超过一半是一样的~~

stl的map和vector用一用简直美滋滋。（c++舒服呀）

还是贴代码吧
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>
using namespace std;
int n,m,x,L;
vector<int> a,b;
map<vector<int>,bool> ma;
bool ok;
vector<int> fz(int k,vector<int> V)//英语渣渣，只好首字母缩写，翻折
{
	vector<int> u;
	u.clear();
	u.push_back(0);
	int l=V.size()-1,e=0;
	int t=max(k,l-k);
	for(int i=t;i>=1;i--)
	{
		int z=0;
		if(k-i+1>0) z+=V[k-i+1];
		if(k+i<=l)	z+=V[k+i];
		e++;
		u.push_back(z);//把新序列放进一个vector
	}
	return u;//vector可以作为函数返回值； 
}
bool pd(vector<int> V)
{
	for(int i=1;i<=m;i++)
	if(V[i]!=b[i]) return 0;
	return 1;
}
void dfs(vector<int> V)
{
	if(ma.count(V)) return;
	ma[V]=1;  //map判重，类似hash，但有一个log 
	int l=V.size()-1;
	if(l==L) if(pd(V)) ok=1;
	if(l<L) return;
	for(int i=0;i<=l;i++)//枚举翻折的位置
	{
		dfs(fz(i,V));
		if(ok) return;
	}
}
int main()
{
	while(cin>>n)//cin卡了点，但数据小的时候是个好东西
	{
		a.clear();
		b.clear();
		a.push_back(0);
		b.push_back(0);
		ma.clear();
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			a.push_back(x);
		} 
		cin>>m;
		for(int j=1;j<=m;j++)
		{
			cin>>x;
			b.push_back(x);
		}
		L=b.size()-1;
		ok=0;
		dfs(a);
		if(ok) cout<<"S"<<endl;
		else cout<<"N"<<endl;
	}
}
```


---

## 作者：Dangerou (赞：4)

## **原题传送门：**[hzwer 爱折纸](https://www.luogu.com.cn/problem/P2809)

## 解题思路：

拿过题来，映入眼帘的就是本题良心的数据范围：$1≤n≤15$ 。可以确定，暴力搜索加上一些奇奇怪怪的特判就可以解决。

但如何实现呢？不难想到深度优先搜索，边界条件就是当现在的纸条序列长 $len$ 等于理想纸条序列的长度 $m$ 时。当然，需要把理想序列的倒序也判断了。最后就是实现纸条翻折的操作，很简单，这里就不详细讲解了（下面的代码中有注释）。

~~建议每次搜索时把目标序列出入函数中否则会很麻烦（亲身体验）。~~

代码实现：
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
#include<string>
#include<cstring>//头文件不解释
using namespace std;
int n,m;
int a[1001];
int b[1001];//变量的申请
bool dfs(int len,int c[])// len 是当前纸条序列的长度，数组c是当前纸条序列
{
    if(len==m)//搜索的边界条件
    {
        bool t1=0;//是否是理想纸条序列
        bool t2=0;//是否是理想纸条序列的倒序
        for(int i=1;i<=len;i++)//注意比较理想纸条序列
        {
            if(c[i]!=b[i])
            {
                t1=1;
                break;
            }
        }
        if(!t1)//是理想纸条序列，则返回1
        {
            return 1;
        }
        for(int i=1;i<=len;i++)//逐一比较理想纸条序列的倒序
        {
            if(c[len-i+1]!=b[i])
            {
                t2=1;
                break;
            }
        }
        if(!t2)////是理想纸条序列倒序，则返回1
        {
            return 1;
        }
        return 0;//如果都不是，则返回0
    }
    int d[1001];//数组d一定要在函数内部申请
    bool ans=0;
    for(int i=1;i<=len-1;i++)//从1开始枚举折叠的位置
    {
        if(max(len,len-i)<m)//如果目标纸条序列的长度比理想纸条序列的长度小，则跳过本次循环
        {
            continue; 
        }
      //因为当前纸条序列长度一半之前的位置和之后的位置折叠时方法是不同的，所以特判成两部分写
        if(i<=len/2)//目标纸条序列长度小于当前纸条序列的长度的一半
        {
            for(int j=1,k=len;k>=i+1;j++,k--)//先取出len到折叠位置之后的序列，存放到数组d中
            { 
                d[j]=c[k];
            }
            for(int j=len-i,k=i;k>=1;j--,k--)//将1到折叠位置的序列对称加到数组d中
            {
                d[j]+=c[k];
            }
        }
        else//目标纸条序列长度大于当前纸条序列的长度。
        {
            for(int j=1;j<=i;j++)//先取出1到折叠位置的序列
            {
                d[j]=c[j];
            }
            for(int j=i,k=i+1;k<=len;j--,k++)//将折叠位置之后到len的序列对称加到数组d中
            {
                d[j]+=c[k];
            }
        }
        ans|=dfs(max(i,len-i),d);//因为在合并序列时，长度是两部分中较长的部分的长度，所以取max
      //因为题目要求只要存在至少一种方案存在即可，所以对ans进行|运算
    }
    return ans;//返回ans的值
}
int main()
{
    while(scanf("%d",&n)!=EOF)//基本的输入不讲了
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);//基本的输入不讲了
        }
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&b[i]);//基本的输入不讲了
        }
        if(dfs(n,a))//开始搜索
        {
            printf("S\n");
        }
        else
        {
            printf("N\n");
        }
    }
    return 0;//完结撒花
}
```
![](https://img-blog.csdnimg.cn/img_convert/03579e28554e905a5191c715b530a335.gif)


---

## 作者：glorious_dream (赞：3)

### 思路分析：

先分析一下题意：通过翻转变换，让已知的纸条变为理想的纸条，求是否能实现。

看到题目的要求，很容易想到这道题要用深度优先搜索。

数据：$70$ 分 ： $N ≤ 10$ （良心啊）爆搜就能过。

$100$ 分 ： $N ≤ 15$ 这就需要~~亿~~一点点技巧了。


------------


### 解题技巧：

考虑操作的等效性，发现枚举翻折线时，只需要枚举前半部分的翻折线，因为当翻折线在后半部分的时候，就相当于先整体翻折，翻折线就到了前面。

最后统计答案的时候，考虑这个数组，如果回文序列和目标纸条相同也算可以做到。


------------


### 代码+解释：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读不解释
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 1010;
int a[M],b[M];
int n,m;
bool dfs(int len,int *s){ // len表示当前数组的长度，s数组表示要被翻折的数组
    if(len == m){ //如果当前的长度和要匹配的长度相当，开始判断符不符合
        bool f1=1,f2=1; //别忘了是两个，回文相同也可以
        for(register int i(1) ; i<=m ; i=-~i){
            if(s[i] != b[i]){ //正着匹配，如果有不同的话，把f1标为false
                f1=0;
                break;
            }
        }
        for(register int i(1) ; i<=m ; i=-~i){
            if(s[len-i+1] != b[i]){ //反着匹配，也就是回文匹配，其余相同
                f2=0;
                break;
            }
        }
        if(f1 || f2) return 1; //如果两个中有一个能匹配，就表示可以，返回1
        return 0; //都不能的话返回0
    }
    bool ans=0; //表示能不能成功匹配
    int d[M]; //用来记录翻折后的数组
    for(register int i(1) ; i<=len-1 ; i=-~i){ //从1开始枚举翻折的位置
        if(len < m) continue; //如果此时的len已经小于m了，没有继续的必要了
        if(i <= len/2){ //翻折的位置在前半段
            for(register int j(1),k(len) ; k>=i+1 ; --k,j=-~j) 
                d[j] = s[k]; //模拟翻折过程，先把s翻折线后面的位置赋值
            for(register int j(len-i),k(i) ; k>=1 ; --k,--j) 
                d[j] += s[k]; //根据题目要求，把s剩下的数加到d的后几位中
        }
        else{ //翻折的位置在后半段
            for(register int j(1),k(1) ; k<=i ; k=-~k,j=-~j) 
                d[j] = s[k]; //同样，先把s的数组赋值给d
            for(register int j(i),k(i+1) ; k<=len ; k=-~k,--j) 
                d[j] += s[k]; //然后把s数组剩下的数加到d数组里面
        }
        
        //以上操作画个草图，模拟一下过程，很容易理解
        
        ans = ans | dfs(max(i,len-i),d); //注意要"|"，有1则1
    }
    return ans; //最后返回能不能做到
}
signed main(){
    while(scanf("%d",&n)!=EOF){ //多组数据读入方法
        for(register int i(1) ; i<=n ; i=-~i) a[i] = read();
        m=read();
        for(register int i(1) ; i<=m ; i=-~i) b[i] = read();
        if(dfs(n,a)) printf("S\n"); //如果能通过翻折匹配，输出S
        else printf("N\n"); //不能的话输出N，别忘了换行
    }
    return 0; //完美收官
}

```
#### ~~喜欢别忘点赞~~

---

## 作者：LJ07 (赞：2)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/P2809)

## 思路简述

考虑搜索。

每次枚举折叠的位置，然后模拟折叠操作即可。

但是这显然是过不了的，我们有以下剪枝：

+ 如果初始状态的所有数字和和目标状态的所有数字和不相等，直接输出 ```N```。
+ 如果当前的数都大于 $0$ 且当前状态的最小值大于目标状态的最小值，当前状态的最大值大于目标状态的最大值，那么停止搜索（反之同理）。
+ 判断是否到达最终状态时要正序反序判断。
+ 其他剪枝：判重等（然鹅没写）

## 丑陋の代码
码风毒瘤，谨慎食用

[click_here](https://www.luogu.com.cn/paste/qzh7v5we)

---

## 作者：Link_Space (赞：2)

直接暴力搜索即可，由于 $N \le 15$ ，所以可以直接枚举每一种翻折情况，dfs数组中传一个当前数列，如果长度和目标数列的长度不相同的话说明还需要继续翻折，如果已经相同了就直接判断每一位和目标序列是否相同即可，注意题目中提到可以将整个序列倒换顺序，所以还要判断倒过来后与目标序列是否相同。

而提到翻转整个序列这个操作，不难想到在翻折过程中我们是不需要这个操作的，只有在最后统计答案的时候需要判断。

接下来就是爆搜了，详情看代码注释：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 100;
int pre[N];
int nxt[N];
int n, m;
bool dfs(int nowlen,int a[])//当前序列长度和当前序列
{
    if(nowlen==m)//判断当前序列与目标序列是否相等
    {
        bool flag = false;
        bool can = false;
        for (int i = 1; i <= m;i++)
        {
            if(a[i]!=nxt[i])
            {
                flag = true;
                break;
            }
        }
        if(!flag)
            return 1;
        for (int i = 1; i <= m;i++)
        {
            if(a[i]!=nxt[m-i+1])
            {
                can = true;
                break;
            }
        }
        if(!can)
            return 1;//正或者反只要相等都可以
        return 0;//如果正或者反都不相等则说明不可行，因为如果再次翻折的话序列长度必定会减小，更不会与目标序列相等
    }
    int temp[16];
    bool ans = false;
    for (int i = 1; i <= nowlen - 1;i++)//判断翻折的位置，将1-i的数往右翻过来
    {
        if(max(i,nowlen-i)<m)
            continue;//如果翻折之后长度比目标序列小的话就不是一个可行的方案
        int to = i + 1;
        int from = i;
        int cnt = 0;
        while(from&&to<=nowlen)
        {
            temp[++cnt] = a[from] + a[to];
            from--;
            to++;
        }
        if(!from)
        {
            while(to<=nowlen)
                temp[++cnt] = a[to++];
        }
        else 
        {
            while(from)
                temp[++cnt] =a[from--];
        }//模拟翻折
        ans = max(dfs(cnt, temp), ans);//寻找到一种可行方案即可
    }
    return ans;
}
int main()
{
    while(scanf("%d", &n)!=EOF)
    {
        for (int i = 1; i <= n;i++)
            scanf("%d", &pre[i]);
        scanf("%d", &m);
        for (int i = 1; i <= m;i++)
            scanf("%d", &nxt[i]);
        if(dfs(n,pre))
            puts("S");
        else
            puts("N");
    }
    return 0;
}
```


---

## 作者：Slient_QwQ (赞：2)

## 分析
爆搜的思路不难想到，就是将翻折的操作进行模拟，再将翻折后的数组进行 dfs 然后重复该操作。

但是处理翻折操作十分复杂，中间的细节很多。

- 首先纸条可以翻转，大部分人都看到了，所以在爆搜中加入了翻转的操作，但只需要在判定时反向的也判一次就行了，至于正确性你们可以自行思考。

- 纸条的翻折可以分为折痕在左边还是在右边，进行分类处理即可。
## Code
```cpp
  #include <bits/stdc++.h>
  using namespace std;
  const int N = 55;
  int a[N], b[N], n, m;
  bool flag;
  void dfs(int num[], int len)
  {
      if (len < m || flag)return;
      int tmp[N];
      for (int i = 1; i <= len; i++)tmp[i] = num[i];
      if (len == m)
      {
          bool pos1 = 1, pos2 = 1;
          for (int i = 1; i <= len; i++)
              if (num[i] != b[i])
              {
                  pos1 = 0;
                  break;
              }
          for (int i = 1; i <= len; i++)
              if (num[len - i + 1] != b[i])
              {
                  pos2 = 0;
                  break;
              }
          if (pos1 || pos2)
          {
              flag = 1;
              return;
          }
      }
      for (int i = 1; i < len; i++)
      {
          for (int j = 1; j <= len; j++)tmp[j] = num[j];
          if (max(len - i, i) < m)continue;
          if (i <= len / 2)
          {
              for (int j = len, k = 1; k <= len - i; j--, k++)tmp[k] = num[j];
              for (int j = len - i, k = i; k; j--, k--)tmp[j] += num[k];
          }
          else
          {
              for (int j = 1; j <= len; j++)tmp[j] = num[j];
              for (int j = i, k = i + 1; k <= len; j--, k++)tmp[j] += num[k];
          }
          dfs(tmp, max(len - i, i));
      }
  }
  int main()
  {
      while (cin >> n)
      {
          for (int i = 1; i <= n; i++)cin >> a[i];
          cin >> m;
          for (int i = 1; i <= m; i++)cin >> b[i];
          flag = 0;
          dfs(a, n);
          cout << (flag ? "S\n" : "N\n");
      }
      return 0;
  }
```


---

## 作者：ZinfI_Sh (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/P2809)

# Step 1

看完题目，第一印象就是 dfs 暴搜，我们只要枚举一个串的折痕，然后模拟翻折就好了。

# Step 2

考虑一些细节：

+ 我们不好枚举折痕，所以我们改为枚举点。设目前串长为 $len$，则枚举点 $1\sim len-1$，折痕为该点右侧。
+ 由于有整体翻转操作，故我们可以只模拟折痕右侧翻到左侧的操作，在判断成立时也判一下目标串的回文串就好了。

# Step 3

具体操作：

1. 枚举翻折点（照上）；
2. 确定翻折后的串的长度，记作 $newlen$；
3. 新创建一个数组 $tmp$，将折叠后的串存到这里；
> 具体来讲，分别考虑左边和右边对于 $tmp_i$ 的贡献，
> 设折痕点位置为 $p$，则左侧提供贡献的位置在 $p-newlen+i$，右侧提供贡献的位置在 $p+newlen-i+1$（自己模拟一下），若超出范围则不作贡献。

4. 将 $tmp$ 递归下去；
5. 若当前串长 $len \lt m$，直接返回；
6. 若当前串长 $len = m$，判断目前串是否与目标串或目标串的回文串相等，如果相等就可以返回成立了。

按照如上步骤模拟一下，就可以轻松求出结果了。

# AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define lowbit(x) (x & -x)
using namespace std;
const int DM[8][2] = {0, 1, 0, -1, 1, 0, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1};
inline void read(int &res)
{
    char ch;
    bool un = 0;
    while (ch = getchar(), !isdigit(ch))
    {
        if (ch == '-')
            un = 1;
    }
    res = ch ^ 48;
    while (ch = getchar(), isdigit(ch))
        res = res * 10 + ch - 48;
    if (un)
    {
        res = -res;
    }
};
int a[101], ans1[101], ans2[101], n, m;
bool check(int len, int arr[101])
{
    if (len != m)
    {
        return 0;
    }
    bool c1 = 1, c2 = 1;
    for (int i = 1; i <= m; i++)
    {
        if (!c1 && !c2)
        {
            return 0;
        }
        if (ans1[i] != arr[i])
        {
            c1 = 0;
        }
        if (ans2[i] != arr[i])
        {
            c2 = 0;
        }
    }
    if (!c1 && !c2)
    {
        return 0;
    }
    return 1;
}
bool dfs(int len, int origin[101])
{
    // for (int i = 1; i <= len; i++)
    // {
    //     cout << origin[i] << ' ';
    // }
    // cout << '\n';
    if (len < m)
    {
        return 0;
    }
    if (len == m)
    {
        if (check(len, origin))
        {
            return 1;
        }
    }
    for (int i = 1; i < len; i++)
    {
        int tmp[101];
        memset(tmp, 0, sizeof(tmp));
        int nlen = max(i, len - i);
        for (int j = 1; j <= nlen; j++)
        {
            int left = i - nlen + j, right = i + nlen - j + 1;
            if (left < 1)
            {
                left = 0;
            }
            if (right > len)
            {
                right = 0;
            }
            tmp[j] = origin[left] + origin[right];
        }
        if (dfs(nlen, tmp))
        {
            return 1;
        }
    }
    return 0;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("qaq.in", "r", stdin);
    // freopen("qaq.out", "w", stdout);
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        cin >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> ans1[i];
            ans2[m - i + 1] = ans1[i];
        }
        if (dfs(n, a))
        {
            cout << "S\n";
        }
        else
        {
            cout << "N\n";
        }
    }
    return 0;
}
```

# 后话

我的分数是 $30\sim70\sim100$ 的过程，错了如下几点：

+ 在判断时，使用的是如下代码段：

```cpp
if (len != m)
    {
        return 0;
    }
    bool c1 = 1, c2 = 1;
    for (int i = 1; i <= m; i++)
    {
        if (!c1 && !c2)
        {
            return 0;
        }
        if (ans1[i] != arr[i])
        {
            c1 = 0;
        }
        if (ans2[m - i + 1] != arr[i])
        {
            c2 = 0;
        }
    }
    return 1;
```

+ 错误是因为结尾没有再判一次；
+ $ans2$ 数组是已经倒叙存储了目标串了，那能 $\tiny{显然}$ 看得出来，`if (ans2[m - i + 1] != arr[i])` 错了吧，应是 `if (ans2[i] != arr[i])`
+ AC！

---

## 作者：Xu_brezza (赞：1)

看了一下题解，好像都是完全按着题走的，提供一个比别的大部分题解更快的做法。

题意： 给一个纸条序列，可以进行翻折（向左折叠）操作，如果折叠过来后有重合的部分，该位置元素变为重合的二者的加和。可以整体翻折，也就是对称过来。
问能否在经过数次变化后得到一个与给定序列相同的序列。

分析： 首先考虑朴素算法，我们暴搜枚举每次翻折线的位置，完全按照题意来模拟，直到得到给定序列，得不到就意味着无解。貌似大部分题解都是这么做的，但这样的复杂度由于每次递归都要枚举翻折点，总的复杂度是 $O(n!)$ 的，虽然好像能过，但我们可以继续优化，毕竟做题是锻炼能力的嘛。

优化： 首先我们发现，如果得到一个完全和给定序列对称的序列，那么显然经过一次翻折变换就可以得到答案，这时已经不用递归下去了。我们再由对称来考虑操作的等效性，想象一下，可以发现，当翻折点在前半部分的时候，变换后的序列等价于：将原序列整体翻折，再从后半部分翻折。二者显然是对称的。这样我们在枚举翻折点的时候，只要枚举后半部分了！复杂度就降了好多，达到了 $O(\left \lfloor \frac{n}{2} \right \rfloor!)$ 。注意判断的时候对称和正着都要判！ 

附上代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
typedef long long ll;
using namespace std;
int flag,n,m,a[21],b[21],c[21];
void dfs(int len,int f){
	if(flag )return;
	if(len == m){
		int f1 = 1,f2 = 1;//一个判对称，一个判正着
		for(int i=1;i<=len;++i){
			if(f1 || f2){
				if(a[i] != b[i])f1 = 0;
				if(a[i] != b[m-i+1])f2 = 0;
			}
			else break;
		}
		if(f1 || f2)flag = 1;//正反判断 
		return;
	}
	int d[21];//就是这里！！！！！回溯用的数组一定开在搜索内部，我就开了全局变量一直WA ，我***** 
	for(int i=1;i<=len;++i)d[i] = a[i];
	int mid = (len + 1) /2,s = (mid > m) ? mid : m;//不能翻折后比m短，小剪枝 
	for(int i=s;i<len;++i){
		int l = i,r = i+1;
		while(l && r <= len)
			a[l--]+=a[r++];//重叠部分加上
		dfs(i,0);//这相当于翻后半部分的
		for(int j=1;j<=len;++j)a[j] = d[j];//回溯 
	}
	if(!f){//整体翻折 在下一次递归的时候会先翻后面，这样等价于翻折点在前半部分，但是是对称的。 
		for(int i=1;i<=len;++i)a[i] = d[len-i+1];//翻过来啦qwq
		dfs(len,1);
	}
}
int main(){
	while(scanf("%d",&n) == 1){
		flag = 0;
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		scanf("%d",&m);
		for(int i=1;i<=m;++i)scanf("%d",b+i);
		dfs(n,0);一定要从0开始因为我们第一次肯定要前半部分，后半部分都作为翻折点的。
		puts(flag ? "S" : "N");
	}
}

```
管理大大求过 qwq 

---

## 作者：moosssi (赞：1)

大水题，直接暴搜即可：

对于最开始的序列，依次枚举翻折的位置，翻折后递归到下一层再次翻折，直到变为目标序列，注意，题目中说过可以翻转，判断的的时候，有从左到右和从右到左两种情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
int a[N],b[N],n,m;
bool flag;
bool dfs(int len,int c[]){//当前序列的长度和序列本身 
	if(len==m){ 
		bool f1=0,f2=0;
		for(int i=1;i<=m;i++){//从左往右 
			if(c[i]!=b[i]){
				f1=1;
				break;
			}
		}
		if(!f1)return 1;
		for(int i=1;i<=m;i++){//从右往左 
			if(c[m-i+1]!=b[i]){
				f2=1;
				break;
			}
		}
		if(!f2)return 1;
		return 0;
	}
	int d[15];
	bool ans=0;
	for(int i=1;i<=len-1;i++){
		if(max(len,len-i)<m)continue;//剪枝，如果翻折后序列长度小于目标长度，则跳过当前情况 
		if(i<=len/2){
			for(int j=1,k=len;k>=i+1;j++,k--){//翻折处理数组 
				d[j]=c[k];
			}
			for(int j=len-i,k=i;k>=1;j--,k--){
				d[j]+=c[k];
			}
		}
		else {
			for(int j=1;j<=i;j++){
				d[j]=c[j];
			}
			for(int j=i,k=i+1;k<=len;j--,k++){
				d[j]+=c[k];
			}
		}
		ans|=dfs(max(i,len-i),d); 
	}
	return ans;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d",&b[i]);
		}
		if(dfs(n,a))printf("S\n");
		else printf("N\n");
	}
	return 0;
}
```


---

## 作者：lwhllw (赞：0)

BFS+hash判重

还有，显然翻折和超过一半的对折是一样的..

然后这题最后一个数据读入... 反正我是被坑了

无线 too many or too few lines

话说在现场的时候，写了半天爆搜结果60分...

还有hash处理负数的时候居然爆了...

还是太弱qaq

noip rp++


```cpp
type arr=array[1..15]of longint;
     node=record
       data:arr;
       head,tail:longint;
     end;
const maxn=15;
      xs=1000003;
var i,j,k,l,m,n,f,e,first,last:longint;
    hashp:array[0..xs]of boolean;
    q:array[1..xs div 10]of node;
    st:node;
function hash(i:node):longint;
var j:longint;
begin
    hash:=0;
    for j:=i.head to i.tail do
      if i.data[j]<0 then hash:=((hash-i.data[j]*100)*100) mod xs
      else hash:=((hash+i.data[j])*100) mod xs;
end;
function check(i:node):boolean;
var j,k:longint;
begin
    if(i.tail-i.head<>st.tail-st.head)then exit(false);
    j:=i.head;k:=st.head;
    while j<=i.tail do
    begin
      if i.data[j]<>st.data[k] then exit(false);
      inc(j);inc(k);
    end;
    exit(true);
end;
procedure init;
var i,j,k:longint;
begin
    fillchar(hashp,sizeof(hashp),true);
    n:=-1;
    readln(n);
    first:=1;last:=1;
    q[1].head:=1;q[1].tail:=n;
    for i:=1 to n do read(q[1].data[i]);
    readln(m);
    st.head:=1;st.tail:=m;
    for i:=1 to m-1 do read(st.data[i]);
    if m<>0 then readln(st.data[m]);
end;
procedure swap(var a,b:longint);
var k:longint;
begin
    k:=a;a:=b;b:=k;
end;
procedure fanp(var p:node);
var i,j,k:longint;
begin
    k:=p.tail;
    for i:=p.head to (p.head+p.tail) shr 1 do
    begin
      swap(p.data[i],p.data[k]);
      dec(k);
    end;
end;
procedure insert(x:node);
begin
    inc(last);
    q[last]:=x;
end;
procedure fanp(var x:node;k:longint);
var i,j,l:longint;
begin
    j:=k-1-(x.tail-k);l:=x.tail;
    for i:=l downto k do
    begin
      inc(x.data[j],x.data[i]);
      inc(j);dec(x.tail);
    end;
end;
procedure bfs;
var i,j,k,o:longint;
    now,l:node;
begin
    o:=0;
    for i:=q[1].head to q[1].tail do inc(o,q[1].data[i]);
    for i:=st.head to st.tail do dec(o,st.data[i]);
    if o<>0 then
    begin
      writeln('N');
      exit;
    end;
    first:=1;last:=1;
    while last>=first do
    begin
      l:=q[first];now:=l;
      fanp(now);j:=hash(now);
      if check(now) then
      begin
        writeln('S');
        exit;
      end;
      if hashp[j] then
      begin
        hashp[j]:=false;
        insert(now);
      end;
      j:=(now.head+now.tail) shr 1;
      now:=l;e:=now.tail;
      inc(j);
      for k:=e downto j do
      begin
        now:=l;
        fanp(now,k);
        o:=hash(now);
        if check(now) then
        begin
          writeln('S');
          exit;
        end;
        if hashp[o] then
        begin
          hashp[o]:=false;
          insert(now);
        end;
      end;
      inc(first);
    end;
    writeln('N');
end;
begin
    {assign(input,'fold.in');
    assign(output,'fold.out');
    reset(input);
    rewrite(output);}
    while not eof do
    begin
      init;
      if m<>0 then
      bfs;
    end;
    {close(input);
    close(output);}
end.

```

---

## 作者：Agumon_ (赞：0)

# 【hzwer爱折纸】
#### ~~考场上做到这题叫折纸来着落谷居然有前缀名233~~
****
**题目的注意点:
**

**hzwer 可以选择任意一条分界线，将整张纸条进行向左翻折， 亦可向右翻折，自己模拟一下可以发现：向左翻折和向右超过一半的对折是一样的**

**鉴于我太蒻了，所以使用了与楼上题解不同的极其暴力的方法**
****

### a[i,j]代表第i次折叠时，此时a数组中第j个数是多少。刚开始读入时读入a[1,j]即可
```
  fillchar(a,sizeof(a),0);
  fillchar(b,sizeof(b),0);
  readln(n);
  if n=0 then exit;//这个数据读入有个坑点，会读到n=0 这时候不管他就好

  tot1:=0;tot2:=0;
  for i:=1 to n do
  begin
    read(a[1,i]);
    tot1:=tot1+a[1,i];
  end;

  readln(m);
  for i:=1 to m do
  begin
    read(b[i]);
    tot2:=tot2+b[i];
  end;
  
  if tot1<>tot2 then
  begin
    writeln('N');
    exit;
  end;

  if (tot1=tot2) and (m=1) then
  begin
    writeln('S');
    exit;
  end;
  
  if check(1,1,n) then writeln('S') else
  writeln('N');
```
- tot1与tot2皆表示a，b数组的和，倘若权值和不同必然不可能折叠；倘若m=1,又权值和相同必然可以折叠。
- 接下来将折叠的次数time，a数组此时的范围l,r进行dfs

### 以下是dfs的内容,有注释233
```pascal

Function: pan_left(time,l,r:longint):boolean;
var i,j,k:longint;
begin
  j:=0;
  for i:=l to r do
  begin
    inc(j);
    if a[time,i]<>b[j] then exit(false);
  end;
  exit(true);
end;

Function: pan_right(time,l,r:longint):boolean;
var i,j,k:longint;
begin
  j:=m+1;
  for i:=l to r do
  begin
    dec(j);
    if a[time,i]<>b[j] then exit(false);
  end;
  exit(true);
end;

Function：check(time,l,r:longint):boolean;
var i,j,k,mid,now:longint;
begin
  len:=r-l+1；//范围长度
  if len<m then exit(false);//当前范围已经小于m了显然exit(false);
  if len=m then//len=m进入判断
  begin
    if (pan_left(time,l,r)) or (pan_right(time,l,r)) then exit(true) else
    exit(false);
  end;//分为从左往右比较以及从右往左比较，如果有一个可以成功就exit(true)

  mid:=(len) shr 1-1;//详情见注意点。
  for i:=l to l+mid do//从左往右折叠过程
  begin
    now:=i;
    for j:=i downto l do
    begin
      inc(now);
      a[time+1,now]:=a[time,now]+a[time,j];
    end;
    while now<r do
    begin
      inc(now);
      a[time+1,now]:=a[time,now];
    end;

    if check(time+1,i+1,r) then exit(true);
  end;

  for i:=r downto r-mid do//从右往左的折叠过程
  begin
    now:=i;
    for j:=i to r do
    begin
      dec(now);
      a[time+1,now]:=a[time,now]+a[time,j];
    end;
    while now>l do
    begin
      dec(now);
      a[time+1,now]:=a[time,now];
    end;

    if check(time+1,l,i-1) then exit(true);
  end;

  exit(false);
end;
```

**希望大家早日AC掉这道~~水~~题（逃**

---

