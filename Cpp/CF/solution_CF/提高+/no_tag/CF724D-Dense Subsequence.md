# Dense Subsequence

## 题目描述

给定长度为n(1 <= n <= 100,000) 的字符串s，现在要求选取一些字符使得每个长度为m 的字符串区间均有一个被选中的字符，且选中的这些字符**重排列**后得到的字符串字典序最小

## 样例 #1

### 输入

```
3
cbabc
```

### 输出

```
a
```

## 样例 #2

### 输入

```
2
abcab
```

### 输出

```
aab
```

## 样例 #3

### 输入

```
3
bcabcbaccba
```

### 输出

```
aaabb
```

# 题解

## 作者：llzzxx712 (赞：6)

这题需要从原序列中选若干个字符，且每个字符之间的间隔不能超过 m ，要使**排列后**选中字符字典序最小。

显然，想要字典序最小，如果有 a ，那我们一定要选上，因为排列后 a 肯定在最前面使字典序小。同样地，如果原序列中没有 a ,我们就要去找 b ，以此类推。

如果原序列中有 a ,但选上所有的 a 后选中字符最大间隔仍大于 m ,我们应该选上所有的 a 后去找 b ,因为字符串" $aaabb..b..$ "的字典序一定小于"$aabb..b..$" ,同理，在找完一个字母后间隔大于 m ,就应该把当前字母全部选上。

当一种字母选完后发现最大间隔小于等于 m ,我们应该在保证最大间隔小于等于 m 的情况下尽量删除字母。因为 $abbb$ 的字典序大于 $abb$ 。

所以我们就可以依次搜索每个字母，如果全选上还是不行，那就全选上并找下一个字母。否则尽量删除。最后输出选中序列。

---

## 作者：Spouter_27 (赞：1)

2021.12.11:最近咕值爆跌，赶快来水一篇题解涨涨咕值......

## CF724D 题解

一道不错的思路题。
#### 题目大意：

给定一个仅由小写字母组成的字符串 $s$ 和一个整数 $m$，要求你从 $s$ 中选出一些字符，满足选出的这些字符在原串中两两间隔不超过 $m$，且将选出的字符排序后，**字典序最小**。输出排列后的选出的字符串。

#### 大体思路：

考虑贪心：从 $\texttt{a}$ 依次遍历到 $\texttt{z}$，每次遍历到一个字母，就把原串中所有该字母标记上，然后判断是否可行：如果不可行就继续找下一个字母，否则尽量删除该字母，删完后输出即可。

#### 正确性证明：

~~感性理解~~

由于 $\texttt{aab}$ 比 $\texttt{abb}$ 字典序小，所以应尽量多选字典序小的字母。

由于 $\texttt{abc}$ 比 $\texttt{abcc}$ 字典序小，所以应尽量删除最后选中的字母。

------------
#### 代码细节：

1. 加完一个字母后判断是否可行：

由于该操作最多会进行 $26$ 次，所以 $O(n)$ 的复杂度是完全可以接受的。所以我们完全可以扫一遍原串，如果有大于等于 $m$ 个连续的字符未被标记，就是不可行的。

2. 可行之后如何尽量删除：

对于已标记的数建立一个双端链表。如果该字符是你想删除的（正在遍历）那个字符，且 $nex_i-lst_i\leq m$，那就把它删掉即可；相信做到这个题的人，链表的删除操作啥的应该都会了吧！

----------
#### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+10;
char s[N];
ll m,n,bj[N],t[27],k=-1,nex[N],las[N];
bool pd(){
	ll lx=0;
	for(int i=0;i<n;i++){
		if(bj[i])	lx=0;
		else lx++;
		if(lx>=m)	return false;
	}
	return true;
}
signed main(){
	scanf("%lld %s",&m,s);
	n=strlen(s);
	for(char c='a';c<='z';c++){
		for(int i=0;i<n;i++){
			if(s[i]==c)	bj[i]=1;
		}
		if(pd()){
			for(int i=0;i<n;i++){
				if(bj[i]==1){
					nex[k]=i;
					nex[i]=n;
					las[i]=k;
					k=i;
				}
			}
			for(int i=0;i<n;i++){
				if(s[i]==c&&bj[i]==1){
					if(nex[i]-las[i]<=m){
						nex[las[i]]=nex[i];
						las[nex[i]]=las[i];
						bj[i]=0;
					}
				}
			}
			break;
		}
	}
	for(char c='a';c<='z';c++){
		for(int i=0;i<n;i++){
			if(s[i]==c&&bj[i]==1)	cout<<c;
		}
	}
	return 0;
}

```
-----------
#### 传送门：

[我的题交记录](https://www.luogu.com.cn/record/64781246)|[洛谷题目链接](https://www.luogu.com.cn/problem/CF724D)|[CF 题目链接](http://codeforces.com/problemset/problem/724/D)

-----------
感谢阅读！蒟蒻文笔不好，大佬轻喷！！！


---

## 作者：TernaryTree (赞：0)

要字典序最小，显然贪心。

首先我们把字符串 `a` 全选上。如果有两个 `a` 相距超过 $n$，那么不满足条件，继续选 `b`。直到符合条件为止。

最后我们得到的东西里面可能有多余的。我们枚举一遍，能删掉就删掉，不能删掉就别删。

具体可以用 `vector` 实现。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
const int maxd = 26;
typedef vector<int>::iterator it;

int n, m;
char s[maxn];
char t[maxn];
int ind[maxd][maxn];
vector<int> vec;
int ed;

int main() {
    cin >> m;
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) ind[s[i] - 'a'][++ind[s[i] - 'a'][0]] = i;
    for (int i = 0; i < maxd; i++) {
        for (int j = 1; j <= ind[i][0]; j++) {
            it pos = lower_bound(vec.begin(), vec.end(), ind[i][j]);
            vec.insert(pos, ind[i][j]);
        }
        bool flag = true;
        for (int j = 1; j < vec.size(); j++) {
            if (vec[j] - vec[j - 1] > m) {
                flag = false;
                break;
            }
        }
        if (!vec.size()) {
            if (n + 1 > m) continue;
            else {
                ed = i;
                break;
            }
        }
        if (vec[0] > m || n + 1 - vec[vec.size() - 1] > m) continue;
        if (flag) {
            ed = i;
            break;
        }
    }
    for (int i = vec.size() - 1; i >= 0; i--) {
        it pos = vec.begin() + i;
        int val = vec[i];
        if (s[val] != 'a' + ed) continue;
        vec.erase(pos);
        bool flag = true;
        for (int j = 1; j < vec.size(); j++) {
            if (vec[j] - vec[j - 1] > m) {
                flag = false;
                break;
            }
        }
        if (!vec.size()) {
            if (n + 1 > m) {
                vec.insert(pos, val);
                continue;
            } else {
                cout << val << endl;
                continue;
            }
        }
        if (vec[0] > m || n + 1 - vec[vec.size() - 1] > m) {
            flag = false;
        }
        if (!flag) {
            vec.insert(pos, val);
            continue;
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        t[i + 1] = s[vec[i]];
    }
    sort(t + 1, t + 1 + vec.size());
    for (int i = 0; i < vec.size(); i++) {
        cout << t[i + 1];
    }
    return 0;
}

```

---

