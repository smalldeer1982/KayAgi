# [POI 2005] BANK-Cash Dispenser

## 题目描述

The BBB (short for Byteotian Bit Bank) owns the largest net of cash dispensers in Byteotia. The clients of the BBB can draw their money from the cash dispensers on the basis of a cash card and a 4-digit PIN code. Lately, in order to increase their clients' security, the BBB has had a camera installed by each cash dispenser. The cameras transmit the recorded image to the BBB using radio signals. Unfortunately, the signals are being intercepted by a gang of computer thieves. The thieves attempt to discover the 4-digit PIN codes of the BBB clients, whose cash cards they subsequently steal. Being aware of this fact, the BBB clients try to perform redundant movements over the keyboard while entering the PIN. The camera is not able to pick out the keystrokes, it only records the finger movements. Consequently, it is usually not possible to determine the PIN unambiguously. For instance, the client moving his finger over the key 1 and then over the key 5 could have entered the following PIN codes: 1111, 1115, 1155, 1555, 5555. Desperate thieves glean the camera recordings, counting on being able to determine the PIN of a client or at least limiting the number of possible codes on the basis of multiple recordings of his transactions. Having accumulated sequences entered by a particular wealthy client of the BBB, they made you an "unnegotiable proposition".

TaskWrite a programme which:

reads from the standard input a description of the recorded sequences of finger movements, which the client has performed whilst entering his PIN,determines the number of distinct PIN codes, which the client can have (i.e. the number of those 4-digit PIN codes, which could have been entered by performing the given finger movement sequences),writes the outcome to the standard output.

BBB（Byteotian Bit Bank的缩写）拥有Byteotia最大的自动提款机网络。 BBB的客户可以根据现金卡和4位数的PIN码从自动柜员机中提取款项。最近，为了提高客户的安全性，BBB已经给每台自动提款机安装了相机。摄像机使用无线电信号将记录的图像发送到BBB。不幸的是，这些信号正被一群电脑盗贼拦截。盗贼试图发现BBB用户的4位PIN码，他们随后窃取了他们的现金卡。意识到这一事实，BBB用户尝试在输入PIN时执行键盘上的冗余动作。相机只能记录手指的动作。因此，通常不可能明确地确定PIN码。例如，用户将手指移动到键1上，然后移动到键5可以输入以下PIN码：1111,1115,1155,1555,5555。绝望的盗贼们收集相机记录，现在盗贼们给你一个手指移动序列，要求你确定用户可以具有的不同PIN码的数量。

写一个程序：

从标准输入读取记录的手指移动序列的描述，用户在输入PIN码时执行的手指移动序列，确定客户端可以具有的不同PIN码的数量（即，这些4位PIN码的数量，这可以通过执行给定的手指移动顺序进入），将结果写入标准输出。


## 样例 #1

### 输入

```
2
3 123
3 234```

### 输出

```
5```

# 题解

## 作者：oscar (赞：22)

【POI补全计划#1-POI2005 BAN】

题意花了半个小时才理解。。可能是我语文太差了

为了防止大家理解不了，我来几句话描述一下

定义一串数字的位置序列是将连续的相同数字只留一个后的结果

举例：2333的位置序列为23,552992999的位置序列为52929

给定 $ n $ 个位置序列( $ n \leq 1000 $,序列长度 $ \leq 10000 $ )，

求十进制4位数的个数，使得该密码的位置序列是每个给定位置序列的子串（可以不连续）

然后解释一下样例

$ n = 2 $

给出的位置序列为123和234

找出公共部分为23

那么可能的4位数就为2222，2223，2233，2333，3333，共5种



--------------题解分割线---------------


考虑每个四位数，只需要判断它的位置序列是不是所有给定位置序列的子串

用10个队列预处理出 “给定的位置序列的第 $ k $ 位（含第 $ k $ 位）后第一次出现数字 $ i $ 的位置，若不存在则为 $ -1 $ ” 的信息，

记录在NEXT[10][1000010]数组里

这样就可以 $ O(1) $ 查询一个不超过4位的位置序列是否是给定的位置序列的子串了

只需要对于每个输入位置序列标记一下不满足条件的4位数，

最后统计没有标记的4位数个数就好了

时间复杂度 $ O( \sum{t} * 10 + 10000 * n ) $

具体实现可能需要卡常，不过我没卡常就过了


AC代码见下


```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
int NEXT[10][10010];
queue<int> num[10];
char buf[23333];
int ok[10000];
int main()
{
    for(int i=0;i<10000;i++)ok[i]=true;
    int n,tmp;
    scanf("%d",&n);
    for(int t=1;t<=n;t++)
    {
        scanf("%d %s",&tmp,buf);
        int len=strlen(buf);
        for(int i=0;i<len;i++)
        {
            num[buf[i]-'0'].push(i);
        }
        for(int i=0;i<len;i++)
        {
            for(int k=0;k<10;k++)
            {
                if(num[k].empty())NEXT[k][i]=-1;
                else NEXT[k][i]=num[k].front();
                //cout<<NEXT[k][i]<<' ';
            }
            num[buf[i]-'0'].pop();
            //cout<<endl;
        }
        int i,j,k,l;
        for(int r=0;r<10000;r++)
        {
            if(ok[r])
            {
                i=r/1000,j=r/100-i*10,k=r/10-i*100-j*10,l=r%10;
                //cout<<i<<j<<k<<l<<endl;
                if(NEXT[i][0]==-1||NEXT[j][NEXT[i][0]]==-1||NEXT[k][NEXT[j][NEXT[i][0]]]==-1||NEXT[l][NEXT[k][NEXT[j][NEXT[i][0]]]]==-1)
                    ok[r]=false;
            }
        }
    }
    int ans=0;
    for(int i=0;i<10000;i++)
        if(ok[i])
            ++ans;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：小黑AWM (赞：5)

##### 看到提交记录中很多人的代码和zyl的长得一模一样，~~屎名警告哦~~qwq
***
在z老师课上一开始茫然半天才弄明白题意，也没太看懂周老师的标程，不过还是十分感谢POI搬运组。

题意oscar巨巨已经简述过了，在此不再赘述，本题解主要提供一种不太一样的写法以及思考过程并且说一下坑点。做法直接跳转到第9段。
***
不难想到我们要枚举0000 - 9999的所有密码输入序列依次检验，不过检验过程中如果强行代入t个动作序列，那么检验的复杂度便是$O(\sum t)$。这必然是不可取的。

那么不妨做一遍LCS再对LCS进行枚举？做一遍$n = 1e3,\space  t= 1e4$的LCS的复杂度怕是要凉。

根据题目性质我们可以增加一些思考，我们手头有的只是四个数字的序列，

我们只要在所有的$t$个序列中找到_有这四个数字的子序列就行了_。

因此我们不需要这个数字的下一个是什么，我们只要知道我们密码数字的后一位在哪儿，寻找过去就是了。

考虑用一个NXT[i][j][k]的数组表示在第i行，第j列，之后（由于我们可以在一个数字上按很多次所以包括其本身）最近的数字k（$k\in[0,9],\space k\in N$）的位置

这个东西只要倒过来维护就可以了。

```cpp
#include <cstdio>
#include <iostream>
#define Int int
using namespace std;
const int maxn = 1e3 + 10;
const int maxt = 1e4 + 10;
int n, t, nxt[maxn][maxt][10], cnt;
char input[maxt];
bool check(int xx, int row){
    int x[5];
    x[1] = xx/1000;
    x[2] = (xx/100)%10;
    x[3] = (xx/10)%10;
    x[4] = xx%10;
    int at = 1;
    for(int i = 1; i <= 4; i++){
        if(nxt[row][at][x[i]] == 0)
            return false;
        at = nxt[row][at][x[i]];
    }
    return true;
}
bool check(int xx){
    for(int i = 1; i <= n; i++)
        if(!check(xx, i))
            return false;
    return true;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> t;
        cin >> input;
        for(int j = t; j >= 1; j--){
            for(int k = 0; k < 10; k++){
                if(k == input[j-1] - '0')
                    nxt[i][j][k] = j;
                else
                    nxt[i][j][k] = nxt[i][j+1][k];
            }
        }
    }

    for(int i = 0; i < 10000; i++)
        cnt += check(i);

    cout << cnt << endl;

    return 0;
}

//60分
```
嗯，提交，MLE。这如果是在NOIP是要爆零的！

我们计算一下空间复杂度，光nxt就有1e8*4bit。[束手无措.jpg]╮(￣▽￣"")╭

脑子钝了好久愣是没想出来怎么优化空间。考虑提取公因式，发现在检验和预处理中在第几行都出现过了，那么我们能不能在每一行就检验一下呢，这样nxt就可以省下n这一维。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#define Int int
using namespace std;
const int maxn = 1e3 + 10;
const int maxt = 1e4 + 10;
int n, t, nxt[maxt][10], cnt;
char input[maxt];
bool great[10000];
bool check(int xx){
    int x[5];
    x[1] = xx/1000, x[2] = (xx/100)%10, x[3] = (xx/10)%10, x[4] = xx%10;
    int at = 1;
    for(int i = 1; i <= 4; i++){
        if(nxt[at][x[i]] == 0)
            return false;
        at = nxt[at][x[i]];
    }
    return true;
}
int main(){
    memset(great, 1, sizeof(great));
    cin >> n;
    for(int i = 1; i <= n; i++){
        memset(nxt, 0, sizeof(nxt));
        cin >> t;
        cin >> input;
        for(int j = t; j >= 1; j--){
            for(int k = 0; k < 10; k++){
                if(k == input[j-1] - '0')
                    nxt[j][k] = j;
                else
                    nxt[j][k] = nxt[j+1][k];
            }
        }
        for(int j = 0; j < 10000; j++)
            great[j] &= check(j);
    }

    for(int i = 0; i < 10000; i++)
        cnt += great[i];

    cout << cnt << endl;

    return 0;
}
//AC
```
# 大功告成！

---

## 作者：lizh (赞：5)

## - P3417 [POI2005]BANK-Cash Dispenser

[P3417 [POI2005]BANK-Cash Dispenser](https://www.luogu.org/problemnew/show/P3417)

这题题意和最长公共子序列很像，但是做法完全不同。因为pin的密码范围为0000—9999，所以我们可以考虑枚举密码，但如果我们判断密码是否成立时用暴力判断，肯定会TLE。

因此我们考虑优化，建立数组Next[k][i]表示第i个数后面（包括自己的位置）第一个k的位置，这样我们用队列预处理，就可以在枚举时用O(1)判断出当前密码是否符合。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const int sum=10000;

queue <int > num[10];
char pin[30000];
int Next[10][30000];
int judge[20000];
void check(int k)
{
	int fi,se,th,fo;
	fi=k/1000,se=k%1000/100,th=k%100/10,fo=k%10;
	if(Next[fi][0]==-1||Next[se][Next[fi][0]]==-1||Next[th][Next[se][Next[fi][0]]]==-1||Next[fo][Next[th][Next[se][Next[fi][0]]]]==-1)
	{
		judge[k]=false;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<=10000;i++) judge[i]=1;
	while(n--)
	{
		int len;
		scanf("%d %s",&len,&pin);
		for(int i=0;i<=len-1;i++)
		{
			num[pin[i]-'0'].push(i);
		}
		for(int i=0;i<=len-1;i++)
		{
			for(int j=0;j<=9;j++)
			{
				if(!num[j].empty()) Next[j][i]=num[j].front();
				else Next[j][i]=-1;
			}
			num[pin[i]-'0'].pop();
		}
		for(int i=0;i<10000;i++)
		{
			if(judge[i])
			{
				check(i);
			}
		}
	}
	long long ans=0;
	for(int i=0;i<10000;i++)
	{
		if(judge[i])
		{
			ans++;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

## - P2425 小红帽的回文数

[P2425 小红帽的回文数](https://www.luogu.org/problemnew/show/P2425)

直接暴力枚举，但是同时要考虑优化。

当答案>sqrt（a）时，答案一定是二进制，有两位相同数字构成，设这两个数为j，所以

#### j*x+j=a;

#### j*(x+1)=a;

#### x=a/j−1;

所以我们就可以考虑枚举j，只要满足j是a[i]的约数，就可以输出x。

代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

bool change(long long x,long long y)//将x转换成y进制下的情况，判断回文数 
{
	long long num[10000];
	long long len=0;
	while(x)
	{
		num[++len]=x%y;
		x/=y;
	}
//	for(int i=1;i<=len;i++)
//	{
//		cout<<num[i];	
//	}
	for(long long i=1;i<=len/2+1;i++)
	{
		if(num[i]!=num[len+1-i]) return false;
	}
	return true;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		long long a;
		scanf("%lld",&a);
		long long y;
		y=sqrt(a);
		int pd=1;
		if(a==2) 
		{
			printf("%d\n",3);
			continue;
		}
		else if(a<=3)
		{
			printf("%d\n",2);
			continue;
		}
		for(long long i=2;i<=sqrt(a)+1;i++)
        {
            if(change(a,i))
            {
                printf("%lld\n",i);
                pd=0;
                break;
             } 
        }
		if(!pd) continue;
		else 
		{
			for(long long i=a/y-1;i>=0;--i)//因为x要最小，所以从大到小枚举 
                if(a%i==0)
                {
					printf("%lld\n",a/i-1);
					pd=0;break;
				}
			if(pd) printf("%lld\n",(a-1)); 
		}
	}
	
	
	return 0;
}
```



---

## 作者：小菜鸟 (赞：3)

作为一道POI的题，其实只有pj的难度。。。

简述题意：

给定n个数字序列。

每一位数字可以展开成任意长度，求有多少长度为4的、这些数字串的公共子序列。

---

显然有一个结论，就是同一个数字选得越靠前越优。

那么对于每一位数字，我们只要记录从它开始往后（包括自身）第一个$0..9$的位置即可。

开一个`next`数组，从后往前扫一遍。

然后枚举所有的四位数，对每一个数字进行判断。

耗时大概$10000 n + \sum t$，绝对可过。

为了防止爆空间，每读入一个数字串就可以判断一次，重用之前的`next`数组。

---

代码

```cpp
#include<cstdio>

const int N=10005;

int n,a[N],next[N][10];

bool invalid[N];

void check(int x)
{
    int t[4];
    t[0]=x/1000;
    t[1]=x/100%10;
    t[2]=x/10%10;
    t[3]=x%10;
    int now=1;
    for(int i=0;i<4;++i)
    {
        if(next[now][t[i]]!=0)now=next[now][t[i]];
        else
        {
            invalid[x]=1;
            return;
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        int len;
        scanf("%d",&len);
        for(int j=1;j<=len;++j)
        {
            scanf("%1d",a+j);
        }
        for(int j=0;j<10;++j)next[len+1][j]=0;
        for(int j=len;j>0;--j)
        {
            for(int k=0;k<10;++k)next[j][k]=next[j+1][k];
            next[j][a[j]]=j;
        }
        for(int i=0;i<10000;++i)
        {
            check(i);
        }
    }
    int res=0;
    for(int i=0;i<10000;++i)res+=!invalid[i];
    printf("%d",res);
}
```



---

## 作者：happybob (赞：0)

考虑爆搜。

对于每一个动作，枚举每一个长度为 $4$ 的数字串，复杂度显然为 $10^4$。由于 $n \leq 10^3$，所以总复杂度为 $10^7$，显然可以。

现在的问题在于，怎么判断一个串是否是可能的 PIN。

即，将这个串中相邻的相同都变成一个后，判断是否是原串的子序列。例如 `1689` 仍然是 `1689`，而 `0064` 就要变成 `064`。

接着判断这个是否是原串的子序列。直接做复杂度是 $O(|s|)$ 的，加上要判断 $10^4$ 次，显然不行。考虑用子序列自动机优化这个过程即可。跑的比较慢，要开 O2 才能过。

启示：判断子序列时，如果原串固定，但有很多匹配串时，子序列自动机可以做到优秀的复杂度。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <set>
#include <vector>
using namespace std;

unordered_map<string, int> mp;
int n;
string p;
bool f = 1;
int x;
bool v[50];
vector<int> g[50];
int son[10005][10];

void dfs(int u, string s)
{
	if (u == 4)
	{
		int now = 0;
		int j = 0;
		for (int p = 0; p < s.size(); p++)
		{
			char k = s[p];
			if (p && k == s[p - 1]) continue;
			if (son[j][k - '0'] == -1) return;
			j = son[j][k - '0'];
		}
		mp[s]++;
		return;
	}
	for (int i = 0; i <= 9; i++)
	{
		if (!v[i]) continue;
		dfs(u + 1, s + (char)(i + '0'));
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		cin >> p;
		for (int j = 0; j <= 9; j++) v[j] = 0, g[j].clear();
		for (auto &j : p) v[j - '0'] = 1;
		for (int j = 1; j <= x; j++) g[p[j - 1] - '0'].emplace_back(j);
		for (int j = 0; j <= x; j++)
		{
			for (int k = 0; k <= 9; k++) son[j][k] = -1;
			for (int k = 0; k <= 9; k++)
			{
				auto it = upper_bound(g[k].begin(), g[k].end(), j);
				if (it != g[k].end())
				{
					son[j][k] = *it;
				}
			}
		}
		dfs(0, "");
	}
	int ans = 0;
	for (auto& y : mp)
	{
		if (y.second == n) 
		{
			ans++;	
		}
	}
	cout << ans << "\n";
	return 0;
}
```


---

