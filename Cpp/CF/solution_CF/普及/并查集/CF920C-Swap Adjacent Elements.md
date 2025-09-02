# Swap Adjacent Elements

## 样例 #1

### 输入

```
6
1 2 5 3 4 6
01110
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6
1 2 5 3 4 6
01010
```

### 输出

```
NO
```

# 题解

## 作者：W1nNy_ (赞：9)

## 题目大意

给定一个正整数序列 ${A_i}$，并且某些位置 $A_i$ 可以与 $A_{i + 1}$ 交换，问能不能通过这种交换，使 $A_i$ 为一个严格递增序列。

## Solution

因为给定的是 01 串来表示能不能交换，所以我们可以将 01 串分为几个全部为 1 的区间，每个区间一定可以交换变成递增序列。

设区间的起点为 $i$，终点为 $j$。

我们只需要判断区间 $s[i\sim j]$ 内的数字是不是从 $i\sim j$ 就可以了。

问题进一步转化，假设前 $k-1$ 个区间已经判断完成，我们需要判断第 $k$ 个区间，那么第 $k$ 个区间 $s[i\sim j]$ 的最小值就应该为 $i$ ， 最大值应该为 $j$ 。

所以对于每一个区间 $s[i\sim j]$ ，如果区间的最小值为 $i$ ， 最大值为 $j$ ，这个区间就是合法的。

但是如果前 $k-1$ 个区间已经判断完成， 我们感性理解一下， 最小值其实并不用判断，我们只需判断最大值就可以了
（最小值不会小于 $k - 1$ 个区间的最大值）。

所以问题最终转化为：

判断每一个区间 $s[i\sim j]$ 内的最大值 $maxx$ 是否和 $j$ 相同。

上代码：

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10;
int a[N],n,maxx;
char s[N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )  scanf("%d",&a[i]);
    scanf("%s",s + 1);
    for (int i = 1; i < n; i ++ )
    {
        maxx = max(a[i], maxx);
        if(s[i] == '0' && i != maxx)
        {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
```
~~萌新OIer,求大佬点赞~~

---

## 作者：yybyyb (赞：3)

每次交换可以拆开看

因为交换是可逆的

所以每次检查一下当前这个数字到他应该去的位置是否可行

检查是否可行，用前缀和检查一下1的个数就好

[强行插入博客](http://www.cnblogs.com/cjyyb/p/8410033.html)
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MAX 250000
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int a[MAX],s[MAX],n,b[MAX];
char sw[MAX];
int main()
{
    n=read();
    for(int i=1;i<=n;++i)a[i]=read(),b[a[i]]=i;
    scanf("%s",sw+1);
    for(int i=1;i<n;++i)s[i]=s[i-1]+sw[i]-48;
    for(int i=1;i<=n;++i)
    {
        int r=b[i],l=i;
        if(r>l)swap(l,r);
        int ss=s[r-1]-s[l-1];
        if(ss!=r-l){puts("NO");return 0;}
    }
    puts("YES");
    return 0;
}
```

---

## 作者：Elgo87 (赞：1)

~~其实吧，我个人觉得这题比较水，难度最多就橙吧...~~

## 题意简述
这题，就是给你一个 $1 \sim N$ 的打乱的排列，其中有若干个元素可以与其后一个元素交换。

题目就是问你，给定这几个可以交换的元素，进行若干次操作后，这个排列可不可以变得有序。

拿样例 1 举例，这个排列是 ```1 2 5 3 4 6```，其中元素 ```2 5 3``` 可以进行操作。

然后我们可以依次交换 ```3,5``` 的位置，排列就变成了 ```1 2 3 5 4 6```，我们再交换 ```5,4``` 的位置，排列就变成了 ```1 2 3 4 5 6```，可以发现它是有序的，所以就输出 ```YES```。

## 思路
既然在指定的范围内可以任意交换元素以达到升序的目的，那我们就可以找到几个**连续的**可交换的数，在这个**连续区间**内进行升序排序，到最后再检查最后得到的序列是否有序。比如下面这个输入样例：
```
7
1 6 5 4 3 2 7
011011
```
我们可以先将**连续的1区间** $[2,3]$ 进行排序，得到新的序列：```1 5 6 4 3 2 7```，然后再将**连续的1区间** $[5,6]$ 进行排序，得到最终的序列：```1 5 6 4 2 3 7```，而这个区间不是有序的，所以这个样例的输出是 ```NO```。

这里要注意一个小小的坑，因为题目要求说的是若干个元素可以和**它后面的元素**交换位置，所以我们对**连续区间**进行排序的时候应该在区间右端点多排一个元素。例如 ```5 4 1 6 2 3``` 中，```4 1 6``` 是可排序的元素，那么我们排序时应该向右多排一个元素，即需要对 ```4 1 6 2``` 进行排序，因为序列中 ```6,2``` 也可以互相交换位置。

## 代码实现
1. 输入不多讲，用 ```n``` 存储元素的个数，$a_{i}$ 存储排列中的第 $i$ 个元素，用 $b_{i}$ 存储 $a_{i}$ 中第 $i$ 个元素是否可以与第 $i+1$ 个元素进行交换。我们这部分代码首先输入 ```n``` 和数组 $a_{i}$，再在第二部分单个读入 $b_{i}$，分别处理。

```cpp
int n,a[200002]={0},b[200002]={0};
cin>>n;
for(int i=1;i<=n;i++)
	cin>>a[i];
getchar();//因为待会迎接的是几个 getchar()，所以这里要吃换行
```


2. 按照思路里的步骤，我们可以定义一个 ```left``` 存储一个**连续的1区间**的左端点，用 ```i``` 去枚举右端点，然后等到 ```i``` 跳出这个区间时 ```sort()``` 一遍区间 $[left,i]$。 那我们怎么找到元素的 1 的左端点呢？我们只要判断一下，如果 $b_{i}=1$ 且 $b_{i-1}=0$，就代表着读到了一个连续的区间，而判断右端点反之即可。

```cpp
int left=0;
for(int i=1;i<n;i++)
{
    char ch=getchar(); //用 getchar() 读入一个 '1' 或 '0'
    b[i]=ch-'0';  //用 b 数组存储 ch
    if(b[i]&&!b[i-1]) left=i; //进入一个连续的区间，判断区间左端点
    if(!b[i]&&b[i-1]) sort(a+left,a+i+1);//跳出一个连续的区间，判断区间右端点
}
//注意这里要特判最后一个端点，因为最后一个端点没有对应的字符可以读入了
if(!b[n]&&b[n-1]) sort(a+left,a+n+1);
```



3. 最后判断一下数组是不是有序的（即数组中有没有[逆序对](https://baike.baidu.com/item/%E9%80%86%E5%BA%8F%E5%AF%B9/11035554?fr=aladdin)）。

```cpp
for(int i=1;i<n;i++)
{
	if(a[i]>a[i+1]) //这是逆序对的情况，即任意一个数大于它后面的数，所以这个数组不再可能是完全的升序，直接输出 NO，然后结束
	{
		puts("NO");
		return 0;
	}
}
puts("YES");//如果数组中没有逆序对了，那么输出 YES。
```


因为代码都一步一步给出了，所以完整代码就不贴了~
###### ~~（抄题解的：呜呜呜呜呜...）~~



---

## 作者：qnqfff (赞：0)

题意：

$n$ 个数,每个数分别是 $1 \sim n$ ,有些数 $i$ 可以和 $i+1$ 交换,问是否能将这 $n$ 个数排序。

思路：

考虑一下把一个数能到达的位置放在一个连通块内,判断每个数的位置和它的值是否在一个连通块内即可,并查集维护。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读
	char ch=getchar();int s=0,f=1;
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') ch=getchar(),f=-1;
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return f*s;
}
int n,a[200010],father[200010];
int find(int x){//并查集
	if(father[x]==x)
		return x;
	return father[x]=find(father[x]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),father[i]=i;//初始化
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
		if(s[i]=='1')
			father[find(i+1)]=find(i+2);//把能到达的位置放在一个连通块内
	for(int i=1;i<=n;i++)
		if(find(i)!=find(a[i])){//判断
			cout<<"NO";
			return 0;
		}
	cout<<"YES";//全都可以
	return 0;
}
```

---

## 作者：kirky_wang (赞：0)

## 题意：
给一串数字序列和一串 $01$ 组成的字符串。如果数字序列中的元素所在下标在字符串中为 $1$，则可以和 $i-1$ 交换。求是否可以得到递增的数字序列。

## 思路：
根据冒泡排序定义可知，任何一个无序序列都可以通过相邻元素交换变成有序的。那么问题就简单了。
如果当前数字不能交换，则判断它是否等于其下标 $+1$。
否则判断找出这一段 $1$ 的右边界（$0$ 或 $\backslash 0$），判断这一段区间内存储的数字是否在下标区间内。如果在区间外则输出 no。将 $j$ 的值赋 $i$。

可以定义一个 $vmin$，$vmax$ 记录区间内的最大值和最小值。事实上，为了节省时间，可以省略 $vmin$，因为已知左边界，所以在遍历数组时判断当前下标的数字是否小于左边界就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200005];
char str[200005];
int main(){
    cin>>n;
    memset(str,0,sizeof(str));
    for(int i = 0; i < n; i++)
        cin>>a[i];
    cin>>str;
    int i,j;
    for(i = 0; i < n; i++){
       if(str[i] == '1'){//如果是1可交换，一直往后到0第一个不可交换的数或字符串结束为止
          int vmax = 0;//记录可交换区间内最大数
          for(j = i; ; j++){
             if(a[j] < i+1){//小于左边界说明不在区间内不符合
                printf("NO\n");
                return 0;
             }
             vmax = max(vmax,a[j]);
             if(str[j] == '0' || str[j] == 0){
                if(vmax > j+1){//如果到了右边界，且区间内的最大值超出右边界不符合
                    printf("NO\n");
                    return 0;
                }
                i = j;
                break;
             }
          }
       }
       else if(a[i] != i+1){//如果是0不可交换，那么这个数必须等于下标+1，否则不对
          printf("NO\n");
          return 0;
       }
    }
    printf("YES\n");
    return 0;
}
```



---

## 作者：oddy (赞：0)

## Description

给定一个整数 $n$ ，一个整型数组 $a_{1..n}$，一个 $01$ 串 $s_{1..n-1}$。

其中 $a$ 是一个 $1 \sim n$ 的**排列**，$s_i$ 表示 $a_i$ 与 $a_i+1$ 能否互换。

问你能否通过有限次符合要求的交换，将 $a$ 还原成 $1 \sim n$ 的**序列**。

如果能，输出 `YES`，否则输出 `NO`。

## Solution

联想到冒泡排序，容易知道，如果对于 $a$ 内的一个区间，任意的相邻两个元素都能交换，那么它一定可以被排成有序的。

则考虑如下操作：

把 $a$ 划分成数量尽量少的几个区间，使得对于每一个区间，任意的相邻两个元素都能交换。然后，对于每一个区间 $a_{l..r}$，检查从 $l$ 到 $r$ 的每一个数在此区间内是否出现。

如果每一个区间都符合要求，则符合题意；否则不符合题意。

坑点：第一个区间的左端点和最后一个区间的右端点要特判。

## Code

```cpp
#include <cstdio>

int n, a[200001], b[200000];

void input() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    for(int i = 1; i < n; i++)
        scanf("%1d", b+i);      // 数字串输入小技巧：格式控制字符 %1d 代表只输入一位
}

int m;
struct node {                   // 用来记录区间
    int l, r;
} range[200001];

void split() {
    range[++m].l = 1;           // 特判
    for(int i = 1; i < n; i++) if(!b[i]) {
        range[m].r = i;
        range[++m].l = i + 1;
    }
    range[m].r = n;             // 特判
}

int vis[200001];

bool judge(int l, int r) {
    // 每次调用前 vis 数组不用清零，请自行思考原因
    for(int i = l; i <= r; i++)
        ++vis[a[i]];
    for(int i = l; i <= r; i++) // 对于从 l 到 r 的每一个数
        if(!vis[i])             // 如果它没出现
            return false;       // 就不符合要求
    return true;
}

void work() {
    for(int i = 1; i <= m; i++) if(!judge(range[i].l, range[i].r)) {
        // 只要有一个区间不符合要求，就不符合题意
        puts("NO");
        return;
    }
    puts("YES");
}

int main() {
    input();
    split();
    work();
    return 0;
}
```



---

## 作者：Great_Influence (赞：0)

可以发现，连续的一段1和最后面的1个0可以互相交换，所以开一个指针记录连续1的开头位置，然后在一路扫，扫到0就可以将l到这个位置的所有数直接sort。最后检查即可。记得剩余的连续1也要处理。

代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&k^'-')k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file(void){
	#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	#endif
}
const int MAXN=2e5+7;
#define Chkmax(a,b) a=a>b?a:b
static int w[MAXN],n;
static char s[MAXN];
inline void init()
{
    read(n);
    Rep(i,1,n)read(w[i]);
    scanf("%s",s+1);
}
inline void solve()
{
    static int l=1;
    Rep(i,1,n)if(s[i]=='0')
    {
        if(s[i-1]!='0')sort(w+l,w+i+1);
        l=i+1;
    }
    if(l!=n)sort(w+l,w+n+1);
    Rep(i,1,n-1)if(w[i]>w[i+1])
    {puts("NO");exit(0);}
    puts("YES");
}
int main(void){
	file();
    init();
    solve();
	return 0;
}

```

---

