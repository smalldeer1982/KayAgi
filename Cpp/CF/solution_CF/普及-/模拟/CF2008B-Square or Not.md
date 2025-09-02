# Square or Not

## 题目描述

漂亮的二进制矩阵是指在四周边缘全为 1 而内部全为 0 的矩阵。

如下图所示为四个漂亮的二进制矩阵的示例。今天，Sakurako 玩了一种大小为 $r \times c$ 的漂亮二进制矩阵，并通过从第一行到第 $r$ 行依次记录每一行的内容，生成了一段二进制字符串 $s$。更具体地，第 $i$ 行第 $j$ 列的元素对应于字符串中的第 $((i-1) \cdot c + j)$ 个字符。

你需要检查，生成字符串 $s$ 的这个漂亮矩阵是否能成为一个方形矩阵。换句话说，你需要判断字符串 $s$ 是否可以由一个边长相等的漂亮二进制矩阵（即 $r = c$）形成。

## 样例 #1

### 输入

```
5
2
11
4
1111
9
111101111
9
111111111
12
111110011111```

### 输出

```
No
Yes
Yes
No
No```

# 题解

## 作者：Super_Cube (赞：1)

# Solution

因为要求最后是正方形，如果 $\sqrt n$ 不是整数一定不合法。

现在使 $n\gets\sqrt n$，那么枚举 $\forall i,j\in[1,n]$，$(i,j)$ 对应 $s_{(i-1)n+j}$，判断是否全部合法。

# Code
```cpp
#include<bits/stdc++.h>
char s[200005];
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%s",&n,s+1);
		if(sqrt(n)!=(int)sqrt(n)){
			nxt:puts("No");
			continue;
		}
		n=sqrt(n);
		for(int i=1,idx=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(s[idx++]!=((i==1||i==n||j==1||j==n)^48))goto nxt;
		puts("Yes");
	}
	return 0;
}

```

---

## 作者：chenxi2009 (赞：1)

# 思路

首先 $n$ 得是一个完全平方数。不是完全平方数压根不是正方形。

然后依次检查它的上下左右是否为 `1`，中间是否为 `0` 就行了。稍微转换一下即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,b;
char s[200001];
bool fal;
int main(){
	scanf("%d",&T);
	while(T --){
		fal = false;
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			s[i] = 0;
			while(s[i] != '1' && s[i] != '0'){
				s[i] = getchar();
			}
		}
		b = sqrt(n);
		if(b * b != n){
			printf("NO\n");
			continue;
		}
		for(int i = 1;i <= b;i ++){
			if(s[i] == '0' || s[b * (b - 1) + i] == '0'){
				fal = true;
				break;
			}
		}
		for(int i = 2;i < b;i ++){
			for(int j = 2;j < b;j ++){
				if(s[(i - 1) * b + j] == '1'){
					fal = true;
					break;
				}
			}
		}
		if(fal){
			printf("NO\n");
		}
		else{
			printf("YES\n");
		}
	}
	return 0;
}
```

---

## 作者：cly312 (赞：0)

先判断 $n$ 是否为完全平方数，然后遍历内部的每个位置，检查这些位置对应的值是否为 $1$ 即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int t;
	cin>>t;
	while(t--){
		int n;
		string s;
		cin>>n>>s;
		int sqn=sqrt(n);
		if(sqn*sqn!=n){
			puts("No");
			continue;
		}
		bool flag=1;
		for(int i=2;i<=sqn-1&&flag;i++){
			for(int j=2;j<=sqn-1&&flag;j++){
				if(s[(i-1)*sqn+j-1]-48){
					puts("No");
					flag=0;
				}
			}
		}
		if(flag) puts("Yes");
	}
    return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# CF2008B Square or Not
## 题目分析
根据题目要求构造出边长为 $\sqrt{n}$ 的正方形，正方形边缘为 $1$，其余为 $0$，将其每一行加入字符串 $s$，最后直接比较 $s$ 与输入即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool a[505][505];
void solve()
{
	memset(a,0,sizeof(a));
	int n;
	cin>>n;
	string s="";
	for (int i=1;i<=sqrt(n);i++)
	{
		for (int j=1;j<=sqrt(n);j++)
		{
			if (i==1||j==1||i==sqrt(n)||j==sqrt(n)) a[i][j]=1; 
			s+=a[i][j]+'0';
		}
	}
	string i;
	cin>>i;
	if (i!=s) cout<<"No\n";
	else cout<<"Yes\n";
}
int main()
{
	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

前言：最顶上的题解代码已被本人 hack，hack 数据放在下面供自测。

第一篇题解 hack 数据：
```
Intput
1
16
1111100111111111
```
```
第一篇题解 Output
Yes
```
```
正解 Output
No
```
第三篇题解并没有说明时间复杂度为什么可以通过，我在这里说明一下：

因为只有当 $n$ 为完全平方数时，答案才有可能是 Yes，所以说只有当 $n$ 是完全平方数时，程序才有可能进入到 $O(\sqrt n \times \sqrt n) = O(n)$ 的循环中，所以说，实际上程序最坏的时间复杂度是 $O(t \times \sqrt {2 \times 10^5}) \approx O(t \times 447)$，是可以过掉的。

其实按理说第三篇题解也过不了，因为如果有一个很善的出题人直接给所有的 $n$ 都附上同一个小于 $2 \times 10^5$ 的最大完全平方数 $199809$，那么所有做法全部寄了，所以说，我认为这道题有一点不严谨。但是还是按照第三篇题解的做法做吧，反正第三篇题解是我认为最优的做法。

代码还是很简单的，就是正常的按照题目说的做就行了。

代码（有注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
char a[N];
int num[N];
signed main()
{
	int _;
	scanf("%d",&_);
	while(_--)
	{
		int n;
		scanf("%d",&n);
		scanf("%s",a+1);
		int s = sqrt(n);
		if(s*s!=n)//当发现n不是完全平方数时
		{
			printf("No\n");
			continue;
		}
		int flag = 1;
		for(int i = 1;i<=s;i++)
		{
			for(int j = 1;j<=s;j++)
			{
				int t = !(i>=2&&i<=s-1&&j>=2&&j<=s-1);//看当前的位置该填什么
				if(a[(i-1)*s+j]!=char('0'+t))//如果输入的字符串这个位置的值跟应该填的值不一样，那就记录下来No
				{
					flag = 0;
					break;
				}
			}
		}
		printf("%s\n",flag?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷](https://www.luogu.com.cn/problem/CF2008B) || [Codeforces](https://codeforces.com/contest/2008/problem/B)

### 简要题意

定义一个 $r\times c$ 的二维 $01$ 矩阵，如果其外圈皆为 $1$，中间为 $0$，那么我们称这个矩阵是美丽的。

我们可以将一个二维 $01$ 矩阵 $a$ 转化为一个字符串 $s$，对于矩阵中的每个元素 $a_{i,j}(1\le i\le r,1\le j\le c)$，对应着 $s_{(i-1)\times c+j}$ 的元素值。

现给出一个长度为 $n$ 的 $01$ 字符串，请问是否能将其构建为一个美丽的二维 $01$ 矩阵，使其为一个正方形，即 $r=c$。

### 思路

假设字符串是由大小为 $r\times c$ 的美丽二进制矩阵创建的。

我们发现当 $r\le 2$ 或 $c\le 2$ 时，那么整个矩阵都是 $1$。那么只有当字符串的大小为 $4$ 时才输出 `Yes`，因为只有 $r=c=2$ 才是一个合适的矩阵。

否则，字符串中至少有一个 $0$。寻找第一个 $0$ 的索引 $id_0$，那么在此之前的所有 $1$ 即为第一行和第二行的第一个格子所组成的外圈，所以易得 $id_0-1$ 即为这个矩阵的边长，那么最后判断是否有 $(id_0-1)^2=n$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, id;
string s;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n >> s;
        id=0; //记！得！初！始！化！
        while (id < n && s[id] == '1') id++; //寻找第一个0
        if(id==n) //序列全为1
            if(n==4) cout<<"Yes"<<endl;//可以组成2*2的美丽矩阵
            else cout<<"No"<<endl;
        else
            if((id-1)*(id-1)==n) cout<<"Yes"<<endl;//判断边长是否为长度的平方根
            else cout<<"No"<<endl;
    }
    return 0;
}
```

---

