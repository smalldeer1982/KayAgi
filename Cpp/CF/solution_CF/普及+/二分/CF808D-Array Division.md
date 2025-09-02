# Array Division

## 题目描述

Vasya has an array $ a $ consisting of positive integer numbers. Vasya wants to divide this array into two non-empty consecutive parts (the prefix and the suffix) so that the sum of all elements in the first part equals to the sum of elements in the second part. It is not always possible, so Vasya will move some element before dividing the array (Vasya will erase some element and insert it into an arbitrary position).

Inserting an element in the same position he was erased from is also considered moving.

Can Vasya divide the array after choosing the right element to move and its new position?

## 说明/提示

In the first example Vasya can move the second element to the end of the array.

In the second example no move can make the division possible.

In the third example Vasya can move the fourth element by one position to the left.

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
2 2 3 4 5
```

### 输出

```
YES
```

# 题解

## 作者：ZZQF5677 (赞：7)

### 解题思路
+ 首先统计 $n$ 个数字和为 $sum$，但是 $sum$ 如果是奇数那就肯定不能了，那么一半就是 $sum = \dfrac{sum}{2} $。

+ 从 $1$ 到 $n$ 枚举，累计进前缀和 $ans$ 中，如果发现第 $i$ 个数字累计进前缀和 $ans$ 中后。

+ 前面 $i$ 个数字中有数字等于 $sum-ans$，那就把这个数字挪到后面 $n-i$ 个中去。

+ 或者剩下的数字中有数字的值等于 $ans - sum$，那就把这个数字挪到前 $i$ 个中去。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 100005;
map<ll, int> mpl, mpr; //分别表示两端数字。
map<ll, int>::iterator it;
int n, a[maxn];
ll sum, ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
    mpr[a[i]]++;
  }
  if (sum % 2) { //sum如果是奇数那就肯定不能了。
    cout << "NO\n";
    return 0;
  }
  int flag = 0;
  sum = sum / 2;
  for (int i = 1; i <= n; i++) {
    ans += a[i]; //累计进前缀和。
    if (ans == sum) {
      flag = 1;
      break;
    }
    mpl[a[i]]++;
    mpr[a[i]]--;
    if (ans > sum && mpl[ans - sum]) {
      flag = 1;
      break;
    }
    if (ans < sum && mpr[sum - ans]) {
      flag = 1;
      break;
    }
  }
  if (flag) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
  return 0;
}

```

---

## 作者：EdenSky (赞：4)

# [CF808D Array Division](https://www.luogu.com.cn/problem/CF808D)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/18340922)

## 思路分析

分析样例 1：

```txt
3
1 3 2
```

原数组被分成 `1` 和 `3 2` 两部分，将 `2` 移到左边即可。

我们设左边部分的和为 $s1$，右边为 $s2$，可以发现对于任何分割方式，只有满足 $s1 \pm x=s2 \mp x$ 才可以继续讨论答案是否成立。

推论 1：由于 $x \in a$（$a$ 为题目所给数列），因此 $| s1-s2 |\equiv 0 \ (\bmod \ 2 )$（换句话说，$s1-s2$ 必然是偶数）。

推论 2：只有当 $\dfrac{|s1-s2 |}{2} \in a$ 时，才能成立。

我们枚举 $p \in [ 0 \ , \ n )$，得出区间 $a_{[1 \ ,\ p ]}$、$a_{[p+1\ ,\ n]}$ 之和，根据以上推论编写代码，可以用桶查询 $\dfrac{| s1-s2 |}{2}$ 是否在原数列。

但真的如此吗？

考虑下面的样例：

```txt
5
1 2 2 5 4
```

这本来应该是 `NO` 的，但如果你只按照上述所说很有可能会输出 `YES`。

按照上面所述，你的程序在将原数列分割成 `1 2 2` 和 `5 4` 时，$\dfrac{| s1-s2 |}{2}=2$，而 2 在桶中是可以被找到的，也就是说，你的程序认为从右边可以往左边移动一个 `2`，这样就成立了。

再仔细看看样例，`2` 分明在左边，右边是没有 `2` 的。

没错，你还要判断当应该从某一边移动数字时，你要判断该数字是否在这一边。

以上就是本道题的思路。如若存在常识性错误，请踢本蒟蒻。

## 代码实现

```cpp
#define by_wanguan
#include<iostream>
#include<map>
#include<vector>
#define int long long
#define pb emplace_back
#define end cout<<"YES",exit(0)
using namespace std;
const int N=1e5+7;
int n,a[N],sum,p,s1,s2;
map<int,vector<int>> vis;
inline int abs(int &a,int &b){
  if(a>b) return a-b;
  else return b-a;
} 
signed main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)
    cin>>a[i],sum+=a[i],vis[a[i]].pb(i);
    //记录a中a[i]出现的位置，方便后续判断abs(s2-s1)/2是否在区间内
  s2=sum,s1=0;
  for(p=0;p<=n+1;p++){//枚举左右区间分界线
    s1+=a[p],s2-=a[p];
    if(abs(s2-s1)%2!=0) continue;
    if(s1==s2) end;
    auto &pe=vis[abs(s2-s1)/2];
    if(s1<s2)
      {if(!pe.empty()&&pe.back()>p) end;}
      //由于上面的位置记录时单调的，只需要取最靠后面的位置就能判断右区间内是否有abs(s2-s1)/2
      //下面同理
    if(s1>s2)
      {if(!pe.empty()&&pe.front()<=p) end;}
  }
  cout<<"NO";
}
```
千万不要用 `unordered_map`，你会后悔的，警钟长鸣。

[喵。](https://www.luogu.com.cn/record/170347518)

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF808D)
## 思路
题目要求我们把 $a$ 数组分成两部分，可以把一个数从一个部分挪到另一个部分，求是否有方案使得两部分的 $\sum$ 相同。

有一个显然的结论，若 $\sum a_i$ 是一个奇数，那么无法组成。

接下来我们考虑决策到了第 $i$ 个数。

设前 $i$ 个数的总和是 $s$，那么可以分成三种情况：

+ $s>\frac{\sum a_i}{2}$，需要从前 $i$ 个数中拿出，判断一下 $\frac{\sum a_i}{2}-s$ 是否存在即可。
+ $s=\frac{\sum a_i}{2}$，直接退出程序。
+ $s<\frac{\sum a_i}{2}$，需要从 $i+1$ 到 $n$ 中拿进，判断一下 $s-\frac{\sum a_i}{2}$ 是否存在即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int a[N];
map<int,int>mp,mpp;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,sum=0,sum1=0;cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i],sum+=a[i],++mpp[a[i]];
    if (sum&1) return cout<<"NO\n",0;
    int exp=sum/2;
    for (int i=1;i<=n;++i){
        sum1+=a[i];++mp[a[i]];--mpp[a[i]];
        if (sum1==exp) return cout<<"YES\n",0;
        if (sum1<exp){
            if (mpp[exp-sum1]) return cout<<"YES\n",0;
        }
        if (sum1>exp){
            if (mp[sum1-exp]) return cout<<"YES\n",0;
        }
    }
    return cout<<"NO\n",0;
}
```


---

## 作者：Clyfort (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF808D)
---
# 解题思路
- 首先统计 $n$ 个数字和为 $sum$，那么一半就是 $sum = sum \div 2$
- 从 $1$ 到 $n$ 枚举，累计进前缀和 $ans$ 中，如果发现第 $i$ 个数字累计进前缀和 $ans$ 中后，前面 $i$ 个数字中有数字等于 $sum - ans$， 那就把这个数字挪到后面 $n - i$ 个中去
- 或者剩下的数字中有数字的值等于 $ans - sum$， 那就把这个数字挪到前 $i$ 个中去

---

# $Code$
```c++
#include <bits/stdc++.h>
using namespace std;
map <long long,long long> c;
map <long long,long long> d;
const int maxn = 1e5 + 5;
long long n, a[maxn], b[maxn], sum;
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		sum += a[i], b[i] = b[i - 1] + a[i], d[a[i]] ++; 
	}
	if (sum % 2 != 0)
	{
		cout << "NO";
		return 0;
	}
	sum /= 2, c[0] = 1;
	for (int i = 1; i <= n; i ++)
	{
		c[a[i]] ++, d[a[i]] --;
		if (d[a[i]] == 0) d.erase(a[i]);
		if (b[i] >= sum)
		{
			if (c[b[i] - sum])
			{
				cout << "YES";
				return 0;
			}
		}
		else
		{
			if (d[sum - b[i]])
			{
				cout << "YES";
				return 0;
			}
		}
	}
	cout << "NO";
	return 0;			
}
```

---

## 作者：kdy20100729 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF808D)  
## 题意简述：  
有一组长度为 $n$ 的数列，问能不能只移动一个数(也可以不移)，使得这一个数列分成两个连续的数列，同时两个数列的和相等。  
## 思路：  
我们先解释下样例：  
第一个样例，把 $3$ 移动到最右边，可得：$1~ 2~ 3$，可以分成两个部分: $\color{red}\boxed{\textbf{1 2}}$ $\color{blue}\boxed{\textbf{3}}$，其中 $1 + 2 = 3$,所以这个样例的答案是 ```YES```。
样例解释完了，咱们再来分析一下策略。既然要使两个数列的和相等，那么原数列的和一定要是偶数 (%$2=0$)，否则直接输出 ```NO```。  
然后从 $1$ 到 $n$，累计进前缀和 $ans$ 中，如果发现第 $i$ 个数字累计进前缀和 $ans$ 中后，前面 $i$ 个数字中有数字等于 $cnt - ans$，那就把这个数字挪到后面 $n - i$ 个中去，或者剩下的数字中有数字的值等于 $ans - cnt$，那就把这个数字挪到前 $i$ 个中去。
## $AC$ 代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool flag;
map<int,int> mp1,mp2;
int n,cnt,ans,a[100005];
map<int,int>::iterator it;
signed main()
{
	cin >> n;
	for(int i=1; i<=n; i++)
	{
		cin >> a[i];
		cnt+=a[i];//统计总和
		mp2[a[i]]++;
	}
	if (cnt%2==1)
	{
		cout << "NO";
		return 0;
	}
	cnt/=2;
	for(int i=1; i<=n; i++)
	{
		ans+=a[i];
		if (ans==cnt)
		{
			flag=true;
			break;
		}
		mp1[a[i]]++;
		mp2[a[i]]--;
		if (ans>cnt&&mp1[ans-cnt]!=0)
		{
			flag=true;
			break;
		}
		if (ans<cnt&&mp2[cnt-ans])
		{
			flag=true;
			break;
		}
	}
	if (flag==true)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

这题没实力。无非就是三种情况：

+ 本身就满足条件。（$1$）
+ 在其后缀中取出一个元素移动到前缀后满足条件。（$2$）
+ 在其前缀中取出一个元素移动到后缀后满足条件。（$3$）

其中（$1$）是简单的，（$2$）和（$3$）直接贪心倒着扫描/正着扫描，判断当前前缀/后缀是否可以从后缀/前缀中移动一个元素满足其值为 $\frac{\sum\limits_{i=1}^n a_i}{2}$ 即可。用 `set` 维护前缀和时间复杂度为 $O(n\log n)$。

```cpp
if(s[n]&1)cout<<"NO\n";
    else{
        int nn=s[n]/2;
        set<int>se;
        G(i,n,1){
            if(s[i]==nn){
                cout<<"YES\n";
                return 0;
            }
            if(s[i]<nn){
                if(se.count(nn-s[i])){
                    cout<<"YES\n";
                    return 0;
                }
            }
            se.insert(a[i]);
        }
        reverse(a+1,a+n+1);
        F(i,1,n)s[i]=s[i-1]+a[i];
        se.clear();
        G(i,n,1){
            if(s[i]==nn){
                cout<<"YES\n";
                return 0;
            }
            if(s[i]<nn){
                if(se.count(nn-s[i])){
                    cout<<"YES\n";
                    return 0;
                }
            }
            se.insert(a[i]);
        }
        cout<<"NO\n";
    }
```

---

## 作者：Ag2WO4 (赞：0)

前排提示：这是一篇 Python 题解喵！

分两种情况：
1. 存在一种分割，左侧数之和比总和一半多 $x$ 的同时 $x$ 刚好在左侧有出现；
2. 存在一种分割，右侧数之和比总和一半多 $x$ 的同时 $x$ 刚好在右侧有出现。

对于刚好无需移动的情况，取等分分割左右位移一位即可。则可遍历序列求前缀和，用集合存储存在历史，作差即可。复杂度是线性的。

代码：
```python
input()#第一行数量提示对 Python 来说是没用的喵!
a = list(map(int, input().split()))
b = sum(a)
if b & 1:#如果总和为奇数是不可能等分的喵！
    print('NO')
    exit()
b >>= 1#总和要取一半方便运算的喵！
c = 0#前缀和喵！
d = set()#存在历史集合喵！
for i in a:
    c+=i;d.add(i)
    if c - b in d:
        print('YES')
        exit()
c = 0
d = set()
for i in a[: : -1]:#倒序重来喵！
    c += i
    d.add(i)
    if c - b in d:
        print('YES')
        exit()
print('NO')
```

---

## 作者：Dream__Sky (赞：0)

令 $sum_l=\sum_{i=1}^{l}a_i,mid=\dfrac{sum_n}{2}$。若 $sum_n$ 为奇数，由于需要平均分成两个数列，故无解。

考虑枚举断点 $i$，对每一个断点分类讨论三种可能：

- $mid>sum_i$，说明我们还需要一个数补齐差距，在断点后寻找是否出现 $mid-sum_i$ 这个数。
- $mid<sum_i$，说明我们断点选的多了，我们需要移动断点前的一个数到后面，在断点前寻找是否出现 $sum_i-mid$。
- $mid=sum_i$，有解。

我们可以用两个 `map` 数组来维护之前要求的前缀出现的数，与后缀出现的数。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100010],sum;
map<int,int> suf,pre;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i],suf[a[i]]++;
	}
	if(sum&1) cout<<"NO",exit(0);
	int mid=sum>>1,sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		suf[a[i]]--;
		pre[a[i]]++;
		if(sum==mid) cout<<"YES",exit(0); 
		if(sum>mid&&pre[sum-mid]) cout<<"YES",exit(0); 
		if(sum<mid&&suf[mid-sum]) cout<<"YES",exit(0); 
	}
	cout<<"NO";
	return 0;
}


```


---

## 作者：Crazyouth (赞：0)

## 分析

令 $sum=\displaystyle\sum_{i=1}^na_i$，若 $sum$ 是奇数，直接 `NO`。

考虑 $sum$ 是偶数，除以二后表示切成两段后一段的和，下面的 $sum$ 表示上文 $sum$ 的二分之一。开两个 map，$fr_i$ 表示前段是否有 $i$ 这个数，$bk_i$ 表示后面那一段是否有 $i$，输入时先丢进 $bk$。顺序枚举 $a$，枚举到的数转进 $fr$，并加进统计变量 $now$，表示现在搜到数的和。如果 $now<sum$，检查 $bk_{sum-now}$，否则检查 $fr_{now-sum}$，是否为真，如果是，直接 `YES`。如果搜完都没有结果，`NO`。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000010];
map<int,int> mp;
int main()
{
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	if(sum%2)
	{
		cout<<"NO";
		return 0;
	}
	sum/=2;
	int now=0;
	for(int i=1;i<=n;i++)
	{
		now+=a[i];
		mp[a[i]]=1;
		if(mp[now-sum])
		{
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}

---

## 作者：Xiphi (赞：0)

exlg 随机跳到的题。我的新年第一题。

考虑枚举分割点，然后判断是否可以通过移动数字的方式使得这个分割点合法。考虑到如果前后之差除以 $2$ 是整数且大的那段里边有前后之差除以 $2$ 这个数的话，则这个分割点是合法的，前后枚举两边即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
map<int,int> mp;
int s1=0,s2=0;
int a[100005];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],s2+=a[i];
	for(int i=0;i<=n;++i){
		s1+=a[i],s2-=a[i];
		int c=s1-s2;
		mp[a[i]]++;
		if(!(c&1)&&c>=0)
		if(mp.count(c/2ll)){
			cout<<"YES";exit(0);
		}
	}
	//后面挪到前边
	s1=0,s2=0,mp.clear();
	for(int i=1;i<=n;++i) s1+=a[i];
	for(int i=n;i>=1;--i){
		s2+=a[i],s1-=a[i];
		mp[a[i]]++;
		int c=s2-s1;
		if(!(c&1)&&c>=0){
			if(mp.count(c/2ll)){
				cout<<"YES";exit(0);
			}
		}
	}
	cout<<"NO";
	return 0;
}




```

---

## 作者：RootMirzayanov (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF808D)

## 题意

给定一个数组, 判断能否将其中一个数字随意移动到一个位置可以使得存在一种分组使数组分成两段, 每段和相等。

## 解析

首先我们计算数组内全部元素的和 $\text{sum}$, 若为奇数则显然不存在。若为偶数则最终答案为 $\dfrac{\text{sum}}{2}$。

同时, 我们可以开一个 `map` 来统计每个数出现的次数。

接下来从前向后遍历数组, 并统计从头开始到现在的和。以将原先所维护的 `map` 中统计到当前遍历到的数的次数减去 $1$ 表示剩余未被统计到的这个数的个数。我们同时可以再开一个 `map` 来统计遍历过程中每个数出现的个数。

- 若统计到的和等于最后答案, 则前后结果的分组为最终答案;

- 若统计到的和大于答案, 则寻找和与答案的差的数字是否被遍历到, 若遍历到只需将这个数移至数组末尾则为合法答案, 否则继续遍历;

- 若统计到的和小于答案, 则寻找答案与和的差的数字是否存在于数组且未被遍历到, 若符合要求只需将这个数移至数组开头则为合法答案, 否则继续遍历。

若遍历完整个数组仍未找到合法答案则不存在, `map` 插入与查询时间复杂度为 $\Theta(\log n)$, 整体时间复杂度为 $\Theta(n\log n)$。

需要注意的是和可能超过 `int` 可表示的范围, 需要用 `long long` 存储。此外用 `unordered_map` 会超时。

## 代码

```cpp
#include <bits/stdc++.h>
int n, a[100000];
long long sum, tmp, ans; 
std::map<long long, int> m, m2;
int main(){
	scanf("%d", &n);
	for(int i = 0;i < n;i++){
		scanf("%d", &a[i]);
		sum+=a[i];
		m[a[i]]++;
	}
	if(sum & 1){
		printf("NO");
		return 0;
	}
	tmp = 0;
	ans = (sum >> 1);
	for(int i = 0;i < n;i++){
		tmp+=a[i];
		m[a[i]]--;
		m2[a[i]]++;
		if(tmp > ans && m2[tmp - ans]){
			printf("YES");
			return 0;
		}
		if(tmp == ans){
			printf("YES");
			return 0;
		}
		if(m[ans - tmp]){
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```

---

## 作者：JustinXiaoJunyang (赞：0)

一道 `D` 题，还是比较简单的。

思路分析：

1. 输入时把每个数字和算出来，如果这个和不是偶数，直接输出 `NO`。

2. 将这个和除以二算出每个部分的目标和 $s$ 是多少。

3. 用一个桶将这些数的值记录下来。

4. 对于前 $x$ 个数，如果和 $s(x)$ 大于 $s$，将和降为 $s$ 要在这 $x$ 个数里查找有没有一个数为 $s(x)-$。

5. 如果 $s(x)<s$，除了这 $x$ 个数里的数中查找有一个数为 $s-s(x)$。

数据范围超大，必须用 `map`。

参考代码：

```cpp
#include <iostream>
#include <map>
using namespace std;

map <long long,long long> m1;
map <long long,long long> m2;

long long n, a[100005], b[100005];

int main()
{
    long long n, s = 0;
    cin >> n;
	for (int i = 1; i <= n; i++) 
	{
		cin >> a[i];
		s += a[i], b[i] = b[i - 1] + a[i], m2[a[i]] ++; 
	}
	if (s % 2 != 0)
	{
		cout << "NO" << endl;
		return 0;
	}
	s /= 2, m1[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		m1[a[i]] ++, m2[a[i]] --;
		if (m2[a[i]] == 0) m2.erase(a[i]);
		if (b[i] >= s && m1[b[i] - s])
		{
			cout << "YES" << endl;
			return 0;
		}
		else
		{
		    if (m2[s - b[i]])
    		{
    			cout << "YES" << endl;
    			return 0;
    		}
		}
	}
	cout << "NO" << endl;
	return 0;			
}
```

---

## 作者：qjxqjx (赞：0)

## 题目思路：
我们先解释下样例：  
第一个样例，把 3 移动到最右边，可得：$1$ $2$ $3$，其中 $1+2=3$，可以分成两个部分。

按这样推下去，我们再仔细思考一下，即可以得知：既然要分成数字和完全相同的两部分，那么我们可以把所有的数加起来再判断奇偶性即可完成第一步。

但是[这样](https://www.luogu.com.cn/paste/wuj7w4eo)的代码并不能过，我们还要模拟一下后面的过程。

从 1 到 n 枚举，累计进前缀和 ans 中，如果发现第 i 个数字累计进前缀和 ans 中后，前面 i 个数字中有数字等于 $sum-ans$， 那就把这个数字挪到后面 $n-i$ 个中去，或者剩下的数字中有数字的值等于 $ans - sum$，那就把这个数字挪到前 i 个中去。

## 代码：
```c
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100005;
map<ll,int> mp1,mp2;
map<ll,int>::iterator it;
int n,a[maxn];ll sum,ans;
int main (){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
		mp2[a[i]]++;
	}
	if(sum%2){
		puts("NO");
		return 0;
	}
	int flag=0;
	sum=sum/2;
	for(int i=1;i<=n;i++){
		ans+=a[i];
		if(ans==sum){
			flag=1;
			break;
		}
		mp1[a[i]]++;
		mp2[a[i]]--;
		if(ans>sum&&mp1[ans-sum]){
			flag=1;
			break;
		}
		if(ans<sum&&mp2[sum-ans]){
			flag=1;
			break;
		}
	}
	if(flag){
		puts("YES");
	}else{
		puts("NO");
	}
	return 0;
}
```


---

## 作者：Level_Down (赞：0)

### 题意简述：

在 $n$ 个数里，能否只移动一个数，使这 $n$ 个数分为和相等的两个部分。

### 方法：

这篇题解不用到二分，思路也比较简单。（其实是不会写二分）

首先我们要边输入边把把每个数字的和算出来，如果这个和不能分成两份（不是二的倍数），直接输出 `NO`。

然后将这个和除以二算出每个部分的目标和 $sum$ 是多少。

在输入的同时我们还要计算前缀和，接下来分析一下方法的主体：

对于原数列的前 $x$ 个数，如果它们的和（这里简称 $sum(x)$ ）大于 $sum$，想要将和降为 $sum$ ，就要在这 $x$ 个数里查找有没有一个数的值为  $sum(x) - sum$。

同理，如果 $sum(x) < sum$，就要从除了这 $x$ 个数里的数中查找有没有一个数的值为  $sum - sum(x)$。

那么问题就来了，怎么查找呢？当然，你想二分我不拦你，但是更好的方法是找一个桶将这些数的值记录下来。

但是 $1 \leqslant a_{i} \leqslant 10 ^ 9$ 明显开数组是不可能了，所以这里我们要用 $map$。

[详细的 $map$ 教程](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-p5266)

上面这段教程虽然不是这题的，但非常适合 $map$ 的入门，不会的可以看看。

有了 $map$ 这题就变得简单了，只需要用 $map$ 查找就可以完美结束了，当然还有一些小细节要注意，这里注释在完整代码上：

```cpp
#include <bits/stdc++.h>
using namespace std;
map <long long,long long> c;//十年OI一场空，不开long long见祖宗。 
map <long long,long long> d;
long long n,a[100005],b[100005],sum;//b数组存前缀和。 
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) 
		{
			cin >> a[i];
			sum += a[i],b[i] = b[i - 1] + a[i],d[a[i]]++; 
		}
	if (sum % 2 != 0) {cout << "NO";return 0;}//part 1。 
	sum /= 2,c[0] = 1;//定 c[0] = 1 就不用特判 sum(x) == sum 的情况了。 
	for (int i = 1; i <= n; i++)//part 2。 
		{
			c[a[i]]++,d[a[i]]--;
			if (d[a[i]] == 0) d.erase(a[i]);//基本操作。 
			if (b[i] >= sum)//如上述判断条件。 
				{
					if (c[b[i] - sum])
						{
							cout << "YES";
							return 0;
						}
				}
				else
					{
						if (d[sum - b[i]])
							{
								cout << "YES";
								return 0;
							}
					}
			}
	cout << "NO";
	return 0;//AC！			
}
```


---

## 作者：UKE自动稽 (赞：0)

**CF808D**

>题目大意：在n个数里，能否只移动一个数，使这n个数分为和相等的两个部分


首先$n$的范围为$1\leqslant n \leqslant 10^5$ ，用暴力会吃不消，所以此题用二分。

现在有10个数字

$a_1 \ a_2 \ a_3 \ a_4 \ a_5 \ a_6 \ a_7 \ a_8 \ a_9 \ a_{10}$

它们的前缀和为$num[10]$

把它们分成两个部分（从$a_4\text{处断开}$）：

$a_1 \ a_2 \ a_3 \ a_4 \| \ a_5 \ a_6 \ a_7 \ a_8 \ a_9 \ a_{10}$

如果移动$a_5$到第一个数列后满足条件

那么第一个数列的和从$num[4]$变为$num[4]+a_5$

而且移动后每段数列为$\Large \frac{sum[10]}{2}$

所以$num[4]={\Large \frac{sum[10]}{2}} - a_5$


现在仍然是这列数（从$a_4\text{处断开}$）：

$a_1 \ a_2 \ a_3 \ a_4 \| \ a_5 \ a_6 \ a_7 \ a_8 \ a_9 \ a_{10}$

如果移动$a_3$到第二个数列后满足条件

那么第一个数列的和从$num[4]$变为$num[4]-a_3$

而且移动后每段数列为$\Large \frac{sum[10]}{2}$

所以$num[4]={\Large \frac{sum[10]}{2}} + a_3$


通过这番推导，我们珂以知道，只要能在这$n$个数中，找到了
$num[n] / 2 ± a[i]$ ，就可以愉快地输出YES了

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int a[111111];
ll num[192608];

bool check(int l, int r, ll x){ //二分查找
    while(l <= r){
        int mid = l + r >> 1;
        if(num[mid] == x)
            return true;
        if(num[mid] > x)
            r = mid - 1;
        if(num[mid] < x)
            l = mid + 1;
    }
    return false;
}

int main(){
    int n;
    cin >> n;
    num[0] = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        num[i] = num[i - 1] + a[i];//维护前缀和
    }
    if(num[n] & 1){
        cout << "NO" << endl;//和为奇数的情况排除
        return 0;
    }
    for(int i = 1; i <= n; i++){
        if(check(i + 1, n, num[n] / 2 + a[i])){查找上述情况
            cout << "YES" << endl;
            return 0;
        }
    }
    for(int i = n; i >= 0; i--){
        if(check(1, i - 1, num[n] / 2 - a[i])){
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
```

---

## 作者：Chang_Pei (赞：0)

### 题目

[这里](https://www.luogu.com.cn/problem/CF808D)

### 思路
首先统计 $n$ 个数字和为 $sum$ ，那么一半就是 $ sum =  \frac{sum}{2}$。

从 $1$ 到 $n$ 枚举，累计进前缀和 $ans$ 中，如果发现第 $i$ 个数字累计进前缀和 $ans$ 中后，


前面 $i$ 个数字中有数字等于 $sum - ans$， 那就把这个数字挪到后面 $n-i$ 个中去。

或者剩下的数字中有数字的值等于 $ans - sum$ ， 那就把这个数字挪到前 $i$ 个中去。

### 代码
```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);++i)
#define efor(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long

using namespace std;

map <ll,int> mp;
map <ll,int> mp2;
ll n,a[100005],sum[100005],s;

int main() {
	cin>>n;
	ffor(i,1,n) {
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		mp2[a[i]]++;
	}
	if(sum[n]%2!=0) {
		cout<<"NO";
		return 0;
	}
	s=sum[n];
	
	s/=2;
	mp[0]=1;
	ffor(i,1,n) {
		mp[a[i]]++,mp2[a[i]]--;
		if (mp2[a[i]]==0) {
			d.erase(a[i]);
		}
		if (sum[i] >= s) {
			if (mp[sum[i] - s]) {
				cout << "YES";
				return 0;
			}
		} else {
			if (mp2[s - sum[i]]) {
				cout << "YES";
				return 0;
			}
		}
	}
	cout<<"NO";
	return 0;
}

```


---

