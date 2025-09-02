# [ABC380C] Move Segment

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc380/tasks/abc380_c

`0`, `1` のみからなる長さ $ N $ の文字列 $ S $ が与えられます。  
 $ S $ の中で先頭から $ K $ 番目の `1` の塊を $ K-1 $ 番目の `1` の塊の直後まで移動した文字列を出力してください。

なお、$ S $ には `1` の塊が $ K $ 個以上含まれることが保証されます。

より正確な説明は以下の通りです。

- $ S $ の $ l $ 文字目から $ r $ 文字目までからなる部分文字列を $ S_{l\ldots\ r} $ と表す。
- $ S $ の部分文字列 $ S_{l\ldots\ r} $ が `1` の塊であるとは、以下の条件を全て満たすことと定める。
  - $ S_l=S_{l+1}=\cdots=S_r= $ `1`
  - $ l=1 $ または $ S_{l-1}= $ `0`
  - $ r=N $ または $ S_{r+1}= $ `0`
- $ S $ に含まれる `1` の塊が $ S_{l_1\ldots\ r_1},\ldots,S_{l_m\ldots\ r_m} $ で全てであり、$ l_1\ <\ \cdots\ <\ l_m $ を満たしているとする。  
   このとき、以下で定義される長さ $ N $ の文字列 $ T $ を、「$ S $ の中で先頭から $ K $ 番目の `1` の塊を $ K-1 $ 番目の `1` の塊の直後まで移動した文字列」と定める
  - $ 1\ \leq\ i\ \leq\ r_{K-1} $ のとき $ T_i\ =\ S_i $
  - $ r_{K-1}+1\ \leq\ i\ \leq\ r_{K-1}+(r_K-l_K)+1 $ のとき $ T_i= $ `1`
  - $ r_{K-1}+(r_K-l_K)+2\ \leq\ i\ \leq\ r_K $ のとき $ T_i= $ `0`
  - $ r_K+1\ \leq\ i\ \leq\ N $ のとき $ T_i=S_i $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\times\ 10^5 $
- $ S $ は `0`, `1` のみからなる長さ $ N $ の文字列
- $ 2\ \leq\ K $
- $ S $ には `1` の塊が $ K $ 個以上含まれる
 
### Sample Explanation 1

$ S $ には、$ 2 $ 文字目から $ 2 $ 文字目、$ 5 $ 文字目から $ 7 $ 文字目、$ 11 $ 文字目から $ 12 $ 文字目、$ 15 $ 文字目から $ 15 $ 文字目の $ 4 $ つの `1` の塊があります。

## 样例 #1

### 输入

```
15 3
010011100011001```

### 输出

```
010011111000001```

## 样例 #2

### 输入

```
10 2
1011111111```

### 输出

```
1111111110```

# 题解

## 作者：Very_Smart_Honet (赞：4)

# 题解 AT_abc380_c [ABC380C] Move Segment

## 题目大意

- 统计序列 $S$ 中，连续 $1$ 的部分有多少个。

- 将第 $k$ 个部分整体向前移，直到第 $k$ 个部分和第 $k-1$ 个部分合并成为一个部分是，输出此时的序列 $S$。

### 数组定义

- $id$ 数组：用于记录第 $i$ 个部分的起始坐标。

- $shu$ 数组：用于记录第 $i$ 个部分的元素个数。

## 思路

从头至尾遍历一遍 $S$，定义临时变量 $number=0$，$cnt=0$，$last=0$。

### 第一部分—处理 连续 $1$ 的部分

- 如果 $S[i]=1$，就让 $number+1$；

- 如果 $S[i]=0$，并且 $s[i-1]=1$。代表这是一个新的部分，进行 $cnt+1$ ，此时将第 $cnt$ 个部分的 $id$ 值赋为 $last$，第 $cnt$ 个部分的 $shu$ 值记为 $number$，并将 $number$ 清 $0$。

- 如果 $S[i]=0$，并且 $s[i+1]=1$。代表即将有一个新的部分，则需要将 $last$ 赋值为下一个部分的起始坐标。

### 第二部分—移动 第 $k$ 个部分

- 我们既然已将统计了每个部分的起始坐标，不妨将第 $k$ 个部分的起始坐标  直接给瞬移到 第 **$k-1$** 个部分的终点坐标的**下一位**，就可以解决顺义问题啦！

- 但有个问题，如何去算终点坐标呢？我们在知道第 $i$ 个部分的起始坐标和数量后，利用 $start+len-1$ 的计算公式，就可以轻松求解了。

### 第三部分—输出序列 $S$

定义临时变量 $now=1$ （用于当前要使用第几个区间）。

- 我们利用计算终点坐标的公式可以算出第 $i$ 个区间的终点坐标，然后判断当前坐标是否在这个区间里。如果在输出 $1$，否则输出 $0$。

- 如果当前坐标的下一个坐标为下一个区间的起始坐标，则更新 $last$ 的值。

## 代码部分

本人认为前面已经很详细了，就不再多说了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
string s;
int id[1000010];
int shu[1000010];
int cnt;
signed main()
{
	cin>>n>>k;
	cin>>s;
	int number=0,last=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='1')
		{
			number++;
		}
		else if(s[i-1]=='1'&&s[i]=='0')
		{
			id[++cnt]=last;
			shu[cnt]=number;
			number=0;
		}
		if(s[i]=='0'&&s[i+1]=='1')
		{
			last=i+1;
		}
	}
	if(number!=0)
	{
		id[++cnt]=last;
		shu[cnt]=number;
		number=0;
	}
	id[k]=id[k-1]+shu[k-1];
	int now=1;
	for(int i=0;i<n;i++)
	{
		if(i>=id[now]&&i<=id[now]+shu[now]-1)
		{
			cout<<1;
		}
		else
		{
			cout<<0;
		}
		if(i+1==id[now+1])
		{
			now++;
		}
	}
	return 0;
}
```

如果大家觉得不错，留个赞再走吧！

---

## 作者：zjj2024 (赞：2)

### 思路
模拟即可。

当 $S_i=1$ 且 $S_{i-1}=0$ 时，发现这肯定是一个整块的分割位置。

计数一下即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	int k,n,cnt=0;
	cin>>n>>k>>s;
	s=' '+s;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='1'&&s[i-1]!='1')cnt++;
		if(cnt==k)
		{
			string t0;
			int j;
			for(j=i-1;j>=1;j--)
			{
				if(s[j]=='1')break;
				t0+='0';
			}
			for(int k=1;k<=j;k++)cout<<s[k];
			int k;
			for(k=i;k<=n;k++)
			{
				if(s[k]!='1')break;
				cout<<s[k];
			}
			cout<<t0;
			for(int p=k;p<=n;p++)cout<<s[p];
			cout<<'\n';
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Binah_cyc (赞：1)

思路很简单，先把所有的连续段都存起来，然后找到第 $k$ 个 $1$ 段，把它和前面的那一段交换。具体的代码实现可以参照我的代码。

代码
```c
// Problem: C - Move Segment
// Contest: AtCoder - AtCoder Beginner Contest 380
// URL: https://atcoder.jp/contests/abc380/tasks/abc380_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
char s[500005];
vector<pair<char,int> > vec;//first存的是这一段的元素种类，second存的是这一段的元素个数
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>s[i];
	int cnt=1;
	for(int i=2;i<=n;i++)//跳过第一个位置
	{
		if(s[i]!=s[i-1]) vec.emplace_back(s[i-1],cnt),cnt=0;//这个位置和上一个位置不同，说明这是一个新块的起点
		cnt++;
	}
	vec.emplace_back(s[n],cnt);//将最后一段推进去
	int num=0;
	for(unsigned i=0;i<vec.size();i++)
	{
		if(vec[i].first=='1') num++;//统计1段的个数
		if(num==k) {swap(vec[i],vec[i-1]);break;}//第k个1段，将它和前面的交换
	}
	for(auto [x,y]:vec) for(int i=1;i<=y;i++) cout<<x;//输出即可
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：1)

> 给定一个 $01$ 串，请把第 $k$ 个全为 $1$ 的极大连通块平移到第 $k-1$ 个这样的连通块的后面，其他不变。

考虑使用一个 `vector`（普通数组也可）记录每个极大 $0/1$ 连通块的长度与内容信息。显然记录的数组内必定为 $01$ 交替。把第 $k$ 个为 $1$ 的连通块与它前面一个元素交换，然后按格式输出即可。

[AC 记录](https://atcoder.jp/contests/abc380/submissions/59844648)。

---

## 作者：Moya_Rao (赞：1)

# 题目大意
给定一个长度为 $N$ 的 `01` 字符串 $S$。定义 `1` 块为 $S$ 中一段全是 `1` 的子串，且这个子串的前一个字符（如果存在）是 `0`，后一个字符（如果存在）也是 `0`。保证 $S$ 中有至少 $K$ 个 `1` 块。

现在你要把第 $K$ 个 `1` 块从 $S$ 中抽取出来，塞到 $S$ 中第 $K-1$ 个 `1` 块的结尾的后面。请输出 $S$ 操作后变成了什么样子。

如果觉得不好理解，那么请看[原题题面](https://atcoder.jp/contests/abc380/tasks/abc380_c)来理解透彻。

# 思路
很简单。细节也不多，赛时一次 AC。

具体怎么做呢，我的做法其实也算复杂的吧，想学更多简便的方法请看题解区里的其他题解。不过你也可以看看我的，了解了解。

我呢，用了四个变量，分别是 $l1$ 和 $r1$，还有 $l2$ 和 $r2$。它们一看就是成双成对的。

具体是么意思呢，$l1$ 和 $r1$ 分别存储的是第 $K-1$ 个 `1` 块的开头结尾的下标，$l2$ 和 $r2$ 分别存储的是第 $K$ 个 `1` 块的开头结尾的下标。我们可以通过遍历一遍字符串 $S$ 来得到它们四个的值，对吧？

那把它们求出来，又有什么用呀？别着急，用处大着呢。接下来不就是输出了么？输出时，一个字符一个字符的输出，至少我是这么干的。

不过要进行一些判断。  
如果当前要输出的第 $i$ 个字符正好是第 $r1$ 个字符，那么先把这个字符原封不动地输出，再要把第 $K$ 个 `1` 块挪过来，所以又要输出 $r2-l2+1$ 个 `1`，用一次循环遍历一遍就是啦。  
如果当前要输出的第 $i$ 个字符是 $l2 \sim r2$ 之间的，那么就不输出啦，因为它们已经在前面被挪走了，不需要再输出一遍。  
其他的情况，给它照常放出来就是了，没有什么特殊滴。

那，不就结束了么？

# [赛时 AC](https://atcoder.jp/contests/abc380/submissions/59841657) 代码
哈哈，我就知道你们爱看这个。没事儿，尽管看，一点儿问题都没有啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l1,r1,l2,r2,cnt;
string s;
int main(){
    cin>>n>>k>>s;
    for(int i=0;i<n;i++){
        if(s[i]=='0')continue;
        int x=i,y=i;
        while(s[i]=='1')i++;
        y=i-1;cnt++;
        if(cnt==k-1)l1=x,r1=y;
        if(cnt==k)l2=x,r2=y;
    }
    for(int i=0;i<n;i++){
        if(i==r1){
            cout<<s[i];
            for(int j=l2;j<=r2;j++)cout<<s[j];
        }
        else if(i>=l2&&i<=r2)continue;
        else cout<<s[i];
    }
    return 0;
}
```

读者朋友们，你都看到这里了，还不赶紧动手点个赞啊？多谢多谢！

也欢迎大家在评论区与我交流本题更多的做法，其他做法或许会比我的更加简便哟！

---

## 作者：Your_Name (赞：0)

## 题意
把第 $k$ 块 $1$ 移到 第 $k-1$ 块 $1$ 后面。
## 题解
直接模拟即可，注意下标的运用和越界的判断。

具体看代码。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n, k, cnt, fl, l, le;
vector<int> ans;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> k >> s;
    for(int i = 0; i < n;){
        if(s[i] == '0'){
            i ++;
            continue;
        }//不是块
        if(s[i] == '1'){
            if(cnt == k - 1){
                l = i;
            }//记录第k块的开始
            int len = 0;
            while(s[len + i] == '1' && len + i < n)len ++;
            i += len;
            cnt ++;
            if(cnt == k - 1){
                fl = i;
            }//记录第k-1块的结束
            if(cnt == k){
                le = len;
            }////记录第k块的长度
        }
    }
    int po;
    for(int i = 0; i < fl; i ++){
        cout << s[i];
        po = i;
    }//输到k-1块的结束
    for(int i = 0; i < le; i ++){
        cout << 1;
        po ++;
    }//输第k个块
    for(int i = 0; i < l - fl; i ++){
        cout << 0;
        po ++;
    }//输中间的0
    for(int i = po + 1; i < n; i ++){
        cout << s[i];
    }//输完
    return 0;
}
```
 _完结撒花_

---

## 作者：xiaoke2021 (赞：0)

好题。

---

> 本文提到的“第 $i$ 段 1”指从左往右数的第 $i$ 段连续的数字 1。

目的是将第 $k$ 段 1 挪到第 $k-1$ 段 1 后面。本质上是将这两段 1 之间的 0 和第 $k$ 段 1 交换位置。

可以先计算出中间的这段 0 的数量，再找到第 $k$ 段 1 的数量，将两部分倒过来输出，其余正常输出即可。计算方式是，跳过前 $k-1$ 段 1，然后逐步统计。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s;
int cnt1,cnt2; // 分别为上文中 0 的数量和 1 的数量
int l=0; // 上文中 0 的起点
int main(){
	cin>>n>>k;
	cin>>s;
	for(int i=1;i<k;i++){
        int pos;
		for(pos=l;pos<n;pos++)
            if(s[pos]=='1')
                break;
		for(l=pos;l<n;l++)
            if(s[l]=='0')
                break;
	}
    // 跳过前 k-1 段 1
	for(int i=0;i<l;i++) cout<<s[i]; // 正常输出
	for(int i=l;i<n;i++,cnt1++)
        if(s[i]=='1')
            break;
	for(int j=l+cnt1;j<n;j++,cnt2++)
        if(s[j]=='0')
            break;
    for(int i=1;i<=cnt2;i++) cout<<'1';
    for(int i=1;i<=cnt1;i++) cout<<'0';
    // 倒过来输出
    for(int i=l+cnt1+cnt2;i<n;i++) cout<<s[i]; // 正常输出
	return 0;
}

```

---

## 作者：ZZ_WYZ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc380_c)

## 题意理解

给定一个长度为 $n$ 由 $0$、$1$ 组成的字符串，所有相连的 $1$ 为一个块，现求将第 $k$ 块移到第 $k-1$ 块后的字符串。

## 思路

1. 记录每个 $1$ 在第几个连通块内。
2. 记录第 $k$ 个连通块的大小 $l$。
3. 将第 $k$ 个连通块所有数标记为 $0$。
4. 最后将第 $k-1$ 后的 $l$ 个数赋值为 $k$。

输出即可。

***注意**：步骤 $3$、$4$ 不能反。（仔细想想）

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,ans[1145141];
int main(){
	string s;
	int n,k;
	cin>>n>>k>>s;
	int sum=0,cnt=1;
	s+='0';
	for(int i=0;i<=n;i++){
		if(s[i]=='1')ans[i]=cnt;
		if(s[i]=='0'&&s[i-1]=='1'){
			cnt++;
		}
	}int ji=0,jii=0;
	for(int i=0;i<=n;i++){
		if(ans[i]==(k-1)){
			ji=i;
		}
	}cnt=0;
	for(int i=0;i<=n;i++){
		if(ans[i]==k){
			cnt++;
		}
	}
	for(int i=ji+1;i<=n;i++){
		if(ans[i]==k)s[i]='0';
		if(cnt!=0)s[i]='1',cnt--;
	}
	for(int i=0;i<n;i++){
		cout<<s[i];
	}
	return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 思路

核心问题就是要把 $1$ 的块给找出来，找到过后就可以按照题意模拟了。

维护两个数 $l,r$，$l$ 初始为 $-1$。

如果当前为 $1$，且下一个为 $0$，那么现在这个点就是右端点，然后就和前面的左端点配对带走。

如果这里是 $1$，并且上一个为 $0$，那么直接把 $l$ 更新给当前点。

然后模拟即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
int n,m;
int a[N];
bool debug = 0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin >> n >> m;
	string s;
	cin >> s;
	vector<pair<int,int> >vec;
	int l = -1,r;
	for (int i = 0; i < s.size(); i ++ ){
		if (s[i] == '1' && l == -1 && (i == 0 || s[i - 1] == '0')){
			l = i;
		}
		if (s[i] == '1' && (s[i + 1] == '0' || i == s.size() - 1)){
			r = i;
			vec.push_back({l,r});
			l = -1;
		}
	}
	for (int i = 0; i < s.size(); i ++ ){
		if (i >= 0 && i <= vec[m - 2].second){
			cout << s[i];
		}
		else if (vec[m - 2].second + 1 <= i && i <= vec[m - 2].second + (vec[m - 1].second - vec[m - 1].first) + 1){
			cout << 1;
		}
		else if (vec[m - 1].second + 1 <= i && i < s.size()){
			cout << s[i];
		}
		else{
			cout << 0;
		}
	}
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

[at原题面](https://atcoder.jp/contests/abc380/tasks/abc380_c)
## 题目分析：
根据题意，找出连续的 $1$ 块，用数组存一下下一个 $1$ 块应移动到的位置，直接大力模拟即可。
## [Code](https://atcoder.jp/contests/abc380/submissions/59875064)

---

## 作者：Kratos_Charger (赞：0)

## AT_abc380_c [ABC380C] Move Segment 题解

### 题目大意

给定一个由 `0` 和 `1`  组成的字符串 $t$，长度为 $n$，要求将字符串中的第 $k$ 个 `1` 的块移动到第 $k-1$ 个 `1` 的块后面，并输出修改后的字符串。

一个 `1` 的块是指一段连续的 `1`，例如字符串 `01111001` 中的 `111` 就是一个块。
在这个问题中，连续的 `1` 构成一个块，目标是将第 $k$ 个 `1` 的块（即第 $k$ 个连续 `1`）移到第 $k-1$ 个块后面，并重新组合字符串。

### 思路

首先遍历字符串 $t$，识别出所有连续的 `1` 和 `0` 的块。将所有的 `1` 的块存储在一个数组 $p$ 中，同时记录块的顺序。

通过遍历找到第 $k-1$ 和第 $k$ 个 `1` 的块位置。将第 $k$ 个块（也就是第 $k$ 个连续的 `1` 的段）移到第 k-1 块的后面。

将处理后的块按顺序拼接成新的字符串，注意，所有 `0` 的块以及除了第 $k$ 个块之外的 `1` 的块都应该按原顺序保留。

当移动块时，确保其他块的位置不变，只有 $k$ 和 $k-1$ 块发生位置交换，保持其他块的位置不变。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string t,p[500005];
int main(){
    cin>>n>>k>>t;
    int cnt=0,st=0,ed=0,res=0;
    for(int i=0;i<n;i++){
        string sg;
        if(t[i]=='1'){
            while(i<n&&t[i]=='1'){
                sg+=t[i++];
            }
            i--;
            p[cnt]+=sg;
            if(res==k-2) st=cnt;
            if(res==k-1) ed=cnt;
            cnt++;
            res++;
        }
		else{
            while(i<n&&t[i]=='0'){
                sg+=t[i++];
            }
            i--;
            p[cnt]+=sg;
            cnt++;
        }
    }
    p[st]+=p[ed];
    for(int i=0;i<cnt;i++)
        if(i!=ed) cout<<p[i];
    return 0;
}

```

---

