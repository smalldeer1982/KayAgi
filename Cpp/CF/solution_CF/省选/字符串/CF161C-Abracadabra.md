# Abracadabra

## 题目描述

$Ploycarpus$分析了一个名为$abracadabra$的字符串，该字符串是用以下的方法构造的：

- 第一步时字符串仅包含单个字符$a$
- 在第$k$步中，我们将第$k-1$步中得到的字符串复制两次，并在这两个串中间插入字母表中的第$k$个字符。$Ploycarpus$所使用的字母表包括小写的拉丁字母和阿拉伯数字，总共$36$个，分别为：第$1$个是$a$，第$2$个是$b$，...，第$26$个是$z$，第$27$个是$0$，第$28$个是$1$，...，第$36$个是$9$。

我们来仔细看一看字符串的构造过程。在第$2$步中，$Ploycarpus$将会把字串"a"复制两次，将字符"b"插在中间，得到字串$aba$。第$3$步会变成"abacaba"，第$4$步会变成"abacabadabacaba"。因此，在第$k$步中，字符串会包括$2^k-1$个字符。

$Polycarpus$写下了用以上的方法在$30$步之后得到的字符串然后选择了两个其中的非空子串。你要做的任务是找到两个$Polycarpus$选择的字串的最长公共子串。

一个字符串$s=s_1s_2...s_{|s|}$的子串$s[i...j](1<=i<=j<=|s|$)即为$s_is_{i+1}...s_j$举个例子，字符串$s=$"abacaba的子串$s[2...4]$就是$bac$。字符串本身可以是它的子串。

最长公共子串即为两个字符串 都包含的最长的子串。比如，"contest"和"test"最长公共子串为"test"。可能有多个最长公共子串（不同组成同长度）

## 样例 #1

### 输入

```
3 6 1 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1 4 4
```

### 输出

```
0
```

# 题解

## 作者：Mooncrying (赞：8)

# CF161C Abracadabra 题解


------------


#### 分治题。


------------

### 题目大意

- 给定一个大字符串的构成方法，求出给定的其中两个子串的最长公共子串长度。

- 大字符串的长度不超过 $2 ^ {30} - 1$。

### 题意分析

- 由于字符串长度很大，我们不能用传统的方式去找它的两个子串分别是什么，需要尝试着换一种方法。

- 考虑到大字符串特殊的构造方式，我们决定从它下手。

	该字符串是经过子串多次复制再在中间添上新的字母得到的，换句话说这是一个很长的**回文串**，且去掉最中间的字母之后分成的两个一模一样的子串依旧是一个**回文串**，于是我们就想到了**分治**。

- 具体的做法就是递归遍历，把当前的原字符串从分成两部分，虽然我们不知道这个字符串长什么样子，但我们知道它左右两部分一模一样，这就可以了。

	当然所求的两个子串肯定包括在当前遍历的字符串中，要不然就没有意义了对吧。
    
    于是我们把它切成两半就像这样：
    
    （注：下图中的蓝线表示**遍历到的大字符串**，黑线表示**题中给出的两个子串**，红线是**分界线**。）
    
    ![1](https://cdn.luogu.com.cn/upload/image_hosting/iul5cb52.png)
    
    或者是这样：
    
    ![2](https://cdn.luogu.com.cn/upload/image_hosting/a2q0s57b.png)
    
    又或者是这样：
    
    ![3](https://cdn.luogu.com.cn/upload/image_hosting/t8i6gvrx.png)
    
    虽然大家都不长一个样，但实际上都差不多。分界线都把两个子串分成了两部分（当然一边啥也没有的那就是空子串呗），我们的遍历都是一样的。
    
    我们已经知道了分解线左右的大字符串是一模一样的（左右蓝线），也就是说我们可以这样去比较：
    
    ![4](https://cdn.luogu.com.cn/upload/image_hosting/y7mmwr1l.png)
    
    （图草了点，轻喷 QAQ。）
    
    具体实现呢，因为两边一样嘛，我们可以把在分解线两侧的子串拉倒同一侧去比较，这样代码也好写些，当然本来在同一侧就没必要啦：
    
	```cpp
	int work(int l1, int r1, int l2, int r2, int now)
	{
		if(r1 < l1 || r2 < l2 || now < 0) return 0;
        	//无法比较或递归到头，返回 0
		int L = max(l1, l2), R = min(r1, r2);
		int ans = L <= R ? R - L + 1 : 0;
        	//首先 ans 存的是两个子串在未分割时候的重叠部分长度，当然不重合就是 0 
		if((l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2)) return ans;
        	//如果两个子串存在相互包含关系，这样公共子串最大长度一定是较短子串的长度，直接输出即可，不然白白浪费时间
		int mid = 1 << now;
		ans = max(ans, work(min(l1, mid), min(r1, mid - 1), min(l2, mid), min(r2, mid - 1), now - 1));
		ans = max(ans, work(min(l1, mid), min(r1, mid - 1), max(l2, mid + 1) - mid, max(r2, mid) - mid, now - 1));
		ans = max(ans, work(max(l1, mid + 1) - mid, max(r1, mid) - mid, min(l2, mid), min(r2, mid - 1), now - 1));
		ans = max(ans, work(max(l1, mid + 1) - mid, max(r1, mid) - mid, max(l2, mid + 1) - mid, max(r2, mid) - mid, now - 1));
        	//四部分的比较，这里所有 min 函数和 max 函数中后面的数都是用来处理子串为空的情况的
            //（接上句）因为没有比较的意义，所以如果一个子串为空，我们就把其所对应的 L 和 R 处理成 L > R，以便在对应的递归函数一开始就让其停止
            //上面的 "- mid" 操作就是把分界线右边的子串拉到左侧
		return ans;
	}
	```
- 实际上写到这儿这个题也就写完了。

### 下面放上无注释代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int l1, r1, l2, r2, answ;
int work(int l1, int r1, int l2, int r2, int now)
{
	if(r1 < l1 || r2 < l2 || now < 0) return 0;
	int L = max(l1, l2), R = min(r1, r2);
	int ans = L <= R ? R - L + 1 : 0;
	if((l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2)) return ans;
	int mid = 1 << now;
	ans = max(ans, work(min(l1, mid), min(r1, mid - 1), min(l2, mid), min(r2, mid - 1), now - 1));
	ans = max(ans, work(min(l1, mid), min(r1, mid - 1), max(l2, mid + 1) - mid, max(r2, mid) - mid, now - 1));
	ans = max(ans, work(max(l1, mid + 1) - mid, max(r1, mid) - mid, min(l2, mid), min(r2, mid - 1), now - 1));
	ans = max(ans, work(max(l1, mid + 1) - mid, max(r1, mid) - mid, max(l2, mid + 1) - mid, max(r2, mid) - mid, now - 1));
	return ans;
}
int main()
{
	scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
	answ = work(l1, r1, l2, r2, 29);
	printf("%d\n", answ);
	return 0;
}
```
完结撒花~

---

## 作者：XL4453 (赞：4)

### $\text{Difficulty : 2400}$
---
### 解题思路：

分治。

考虑从大到小考虑每一个对称轴，然后把每一个区间在对称轴右边的翻到左边来，反正有中间那个字符也匹配不了，只能靠分开的了。两个区间一共四种情况讨论一下就可以了。

注意完全包含的时候直接返回答案，不能在分下去，复杂度会炸。

---
### 复杂度分析：

老实说我一开始想到这个递归的时候以为复杂度是错的，原因是如果简单地将模型抽象为 $T(1)=1$，$T(n)=4\times T(\dfrac{n}{2})+1$ 根据主定理得出的复杂度是 $O(n^2)$（也就是不在完全包含的时候返回的情况）。

但是其实复杂度就是 $O(\log n)$。

这里两个区间感觉很复杂，但是考虑区间的情况也就简单了。

两个区间不互相包含，但是都包含对称轴，考虑下一次操作，上下两个生成两个子区间都是包括对称轴位置的，所以无论哪一个区间包含哪一个都只能产生 $O(1)$ 的贡献。

另一种两个不包含，但是都不包含对称轴，在计算完当前的贡献之后，四种情况只可能有一个有用，而这样的情况由于每一次可能的区间范围都减半，所以最终产生的贡献也不超过 $O(\log n)$，如果卡满就不能产生其他状态。

两者不互相包含，但是有一个包含了对称轴，这种情况下回分裂出两种可能的情况，但是可以发现，如果想要通过这种方法卡复杂度的话需要两个区间卡到下一位置的 $2^n$，但是如果能够做到就出现了 $2^{n-1}$ 到 $2^n$ 整块被覆盖，这在下下此覆盖中只能提供 $O(1)$ 的贡献，以此类推，最后还是只能产生最多 $O(\log n)$ 的贡献，如果卡满就不能产生其他状态。

两块出现交集只需要 $\log n$ 次，也是可以接受的。

这样综合下来的话，最后的时间复杂度就是 $O(\log n)$ 的。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int l1,l2,r1,r2;
int work(int l1,int r1,int l2,int r2,int now){
	if(l1>r1||l2>r2)return 0;
	int ans=max(0ll,min(r1,r2)-max(l1,l2)+1);
	if(((l1<=l2)&&(r2<=r1))||(l2<=l1)&&(r1<=r2))return ans;
	ans=max(ans,work(min(l1,now),min(r1,now-1),max(l2,now+1)-now,max(r2,now)-now,now/2));
	ans=max(ans,work(min(l1,now),min(r1,now-1),min(l2,now),min(r2,now-1),now/2));
	ans=max(ans,work(max(l1,now+1)-now,max(r1,now)-now,min(l2,now),min(r2,now-1),now/2));
	ans=max(ans,work(max(l1,now+1)-now,max(r1,now)-now,max(l2,now+1)-now,max(r2,now)-now,now/2));
	return ans;
}
signed main(){
	scanf("%I64d%I64d%I64d%I64d",&l1,&r1,&l2,&r2);
	printf("%I64d\n",work(l1,r1,l2,r2,1<<29));
	return 0;
}
```


---

## 作者：JK_LOVER (赞：3)

## 题意
给你一个字符串的生成方式，求问 $S[l_1..r_1]$ 和 $S[l_2..r_2]$ 的最长公共子序列。[qwq](https://www.luogu.com.cn/blog/xzc/solution-cf161c)
- 第一步时字符串仅包含单个字符 $a$ 
- 在第 $k$ 步中，我们将第 $k-1$ 步中得到的字符串复制两次，并在这两个串中间插入字母表中的第 $k$ 个字符。

## 分析
无论任何时候这个串都是一个回文串，且第 $k$  步时，回文中心是 $2^{k-1}$ 。那么可以递归构造这两个字符串。那么讨论这个串左右端点和回文中心的位置关系递归下去。注意边界问题。时间复杂度为 $O(\log n)$ 。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int solve(int l1,int r1,int l2,int r2,int S){
	if(r1 - l1 < 0 || r2 - l2 < 0) return 0;
	int L = max(l2,l1),R = min(r1,r2);
	int res = (L <= R) ? R - L + 1 : 0;
	if((l1 <= l2 && r2 <= r1)||(l2 <= l1 && r1 <= r2)) return res;
	int mid = 1 << S;
	res = max(res,solve(min(l1,mid),min(r1,mid-1),min(l2,mid),min(r2,mid-1),S-1));
	res = max(res,solve(min(l1,mid),min(r1,mid-1),max(l2,mid+1)-mid,max(r2,mid)-mid,S-1));
	res = max(res,solve(max(l1,mid+1)-mid,max(r1,mid)-mid,min(l2,mid),min(r2,mid-1),S-1));
	res = max(res,solve(max(l1,mid+1)-mid,max(r1,mid)-mid,max(l2,mid+1)-mid,max(r2,mid)-mid,S-1));
	return res;
}
int main()
{
	int l1,l2,r2,r1;
	cin >> l1 >> r1 >> l2 >> r2;
	int ans = solve(l1,r1,l2,r2,29);
	cout << ans << endl;
	return 0;
}
```



---

