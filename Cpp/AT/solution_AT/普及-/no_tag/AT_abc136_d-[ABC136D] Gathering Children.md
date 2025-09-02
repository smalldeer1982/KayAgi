# [ABC136D] Gathering Children

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc136/tasks/abc136_d

マスの情報を表す、`L` と `R` で構成された文字列 $ S $ が与えられます。

文字列 $ S $ の長さを $ N $ としたとき、$ N $ 個のマスが左右一列に並んでおり、左から $ i $ 番目のマスには $ S $ の左から $ i $ 番目の文字が書かれています。

ただし、左端のマスには必ず `R`、右端のマスには必ず `L` が書かれています。

はじめ、各マスには $ 1 $ 人の子どもが居ます。

子どもたちはそれぞれ次の規則に従った移動を $ 10^{100} $ 回行います。

- 今居るマスに書かれた文字に従って $ 1 $ マス移動する。すなわち、今居るマスに書かれた文字が `L` のとき左隣のマスに、`R` のとき右隣のマスに移動する。

$ 10^{100} $ 回の移動の後に各マスに居る子どもの人数を求めてください。

## 说明/提示

### 制約

- $ S $ は長さ $ 2 $ 以上 $ 10^5 $ 以下の文字列であり、$ S $ の各文字は `L` または `R` である。
- $ S $ の $ 1 $ 文字目は `R`、$ N $ 文字目は `L` である。

### Sample Explanation 1

\- $ 1 $ 回の移動の後に各マスに居る子どもの人数は左のマスから順に $ 0,\ 2,\ 1,\ 1,\ 1 $ 人です。 - $ 2 $ 回の移動の後に各マスに居る子どもの人数は左のマスから順に $ 0,\ 1,\ 2,\ 1,\ 1 $ 人です。 - この移動を $ 10^{100} $ 回行った後に各マスに居る子どもの人数は左のマスから順に $ 0,\ 1,\ 2,\ 1,\ 1 $ 人です。

## 样例 #1

### 输入

```
RRLRL```

### 输出

```
0 1 2 1 1```

## 样例 #2

### 输入

```
RRLLLLRLRRLL```

### 输出

```
0 3 3 0 0 0 1 1 0 2 2 0```

## 样例 #3

### 输入

```
RRRLLRLLRRRLLLLL```

### 输出

```
0 0 3 2 0 2 1 0 0 0 4 4 0 0 0 0```

# 题解

## 作者：dd_d (赞：2)

## Sol   
首先手玩一下样例，很容易可以发现，形如 $RL$ 这样的串，其中的机器人是不断来回走的。  
那我们只需要对不是这样的字串来处理。  
我们提前记下每个 $RL$ 的位置。  
然后枚举一下字符串，对当前位置的字符进行处理。  
若当前字符为 $R$，我们找到当前字符右边的第一个 $RL$，然后计算一下需要几步。  
若步数为偶数，那最后当前位置的机器人会落在 $R$ 上，否则便会落在 $L$ 上。   
若当前字符为 $L$，则找到左边的第一个 $RL$，其余操作不变。  
最后输出答案即可。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e5+1;
string st;
bool b[N];
int n,l,L[N],R[N],ans[N],m1,m2;
signed main() 
{
    cin>>st;
    n=st.length();
    st=' '+st;
    l=1;
    while (l<=n) 
	{
        if (st[l]=='R'&&st[l+1]=='L') 
		{
            ans[l]++;
            ans[l+1]++;
            L[++m1]=l+1;
            b[l]=1;
            b[l+1]=1;
            l+=2;
        } 
		else l++;
    }
//    l=n;
//	while (l>=1)
//    {
//        if (st[l]=='R'&&st[l-1]=='L')
//        {
//            b[l]=1;
//            b[l-1]=1;
//            R[++m2]=l;
//            l-=2;
//        }
//        else l--;
//    }
    l=1;
    while (l<=n) 
	{
        if (b[l]) 
		{
            l++;
            continue;
        }
        int x=0;
        if (st[l]=='R') 
		{
            for (int i=1;i<=m1;i++)
                if (L[i]>l) 
				{
                    x=L[i];
                    break;
                }
        } 
		else 
		{
            for (int i=m1;i>=1;i--)
                if (L[i]<l) 
				{
                    x=L[i];
                    break;
                }
        }
        if (abs(l-x)%2==1) ans[x-1]++;
        else ans[x]++;
        l++;
    }
    for (int i=1;i<=n;i++)
        writesp(ans[i]);
}



```


---

## 作者：yanyan2 (赞：1)

给一个比现在讨论区更简单的题解。

如果对于一段连续的 `R`，每个点都会一直往右走，走到第一个 `L`，然后进入来回跳动的模式。对于一段连续的 `L` 同理，一直往左走，走到第一个 `R`。

设第 $i$ 个点走到 $to_i$ 之后进入来回跳的模式，只需要对 $|to_i - i|$ 进行一个奇偶的分类讨论即可。

对于求解 $to_i$，具体用双指针 $O(N)$ 解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int inline read() {
	int num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n, to[N], ans[N];
char a[N];
int main() {
	scanf("%s", a + 1), n = strlen(a + 1);
	for(int i = 1, p; i <= n; i = p) {
		p = i;
		while(a[i] == a[p])p++;
		for(int j = i; j < p; j++) {
			if(a[i] == 'L')to[j] = i;
			else to[j] = p - 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		int dis = abs(to[i] - i);
		if(dis & 1)ans[to[i] + (a[i] == 'L' ? -1 : 1)]++;
		else ans[to[i]]++;
	}
	for(int i = 1; i <= n; i++)printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：MiddleRed (赞：1)

## Discription  
给定一个长为 $n$ 的只有 $L$ 和 $R$ 的字符串 $S$ ，字符串每一个字符上都有一个点。现在开始 $10^{100}$ 轮移动，每一轮移动，每个字符上的点按照它当前字符上的字母来决定向左还是向右移动，如果为 $L$ 则向左移动一格， $R$ 则向右移动一格。保证字符串开头字符为 $R$ ，末尾字符为 $L$ 。输出经过 $10^{100}$ 轮移动后每个字符上点的个数。  
  
  
## Solution  
模拟+找规律。  
首先不要被 $10^{100}$ 吓到，观察样例和样例解释，发现经过这么多轮前结果其实早就决定了，而不是在最后一轮交换所决定的，这个巨大的数字言下之意就是这个字符串上的点都会聚在某一个位置。而 $10^{100}$ 是偶数，所以我们只要求出点都聚在一起后再经过第偶数轮的答案即可。  
我们可以把字符串看成多个由 $L$ 和 $R$ 所组成的多个区间，每个区间互不干扰，且每个区间内左边都是 $R$ ，右边都是 $L$ 。区间内的点会在这个区间内 $R$ 和 $L$ 的交界处汇集。所以我们先求出每个区间内所有点聚在一起后点的数量的情况，把左边 $R$ 的个数记录在区间内最右边的 $R$ 上，右边 $L$ 的个数记录在区间内最左边的 $L$ 上。  
之后便是找规律看多次移动后点的情况。可以用竖式在Excel里模拟下每轮情况。不难发现，当我们把区间内的点都聚集在区间内 $L$、$R$ 的交界处后，之后的移动就是这两个点上的数字互相交换。对于 $L$、$R$ 数量之和为偶数的情况，点的数量均匀分配，即为 $(L+R)/2$ ，记录在相应位置的结果数组上。对于不是偶数的情况，如果 $L$ 的个数为奇数，则 $L$ 的结果不变， $R$ 的结果为 $R$ 的数量加一，反之亦然。最后顺序输出（记得加空格）。   
$\ $  
非最优解法。
  
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,a[100001],res[100001];
bool ifcr=1,ifcl=0;
int cr,cl,nl;
int main()
{
	cin>>s;
	n=s.length();
	s+='O';
	//统计区间内L R个数
	for(int i=0;i<n+1;i++)
	{
		if(ifcr)
		{
			if(s[i]=='R')	cr++;
			else
			{
				a[i-1]=cr;
				cr=0;
				ifcr=0;ifcl=1;
				nl=i;
			}	
		}
		if(ifcl)
		{
			if(s[i]=='L')	cl++;
			else
			{
				a[nl]=cl;
				cl=0;
				ifcr=1;ifcl=0;
				cr++;
			}
		}
	}
    
	//计算交换情况
	for(int i=0;i<n;i++)
	{
		if(a[i]!=0)
		{
			if((a[i]+a[i+1])%2==0)
			{
				res[i]=(a[i]+a[i+1])/2;
				res[i+1]=res[i];
			}
			else
			{
				res[i]=floor((a[i]+a[i+1])/2);
				res[i+1]=res[i];
				if(a[i]%2==0)	res[i+1]++;
				else res[i]++;
			}
			i++;
		}
	}
	for(int i=0;i<n;i++)	cout<<res[i]<<" ";
	return 0;
}
```

---

