# Alternating String

## 题目描述

# 交替字符串


Sakurako 非常喜欢交替字符串。她把一个由小写拉丁字母组成的字符串 $s$ 称为"交替字符串"，如果字符串中偶数位置的字符都相同，奇数位置的字符都相同，且字符串的长度是偶数。

例如，字符串 `abab` 和 `gg` 是交替的，而字符串 `aba` 和 `ggwp` 则不是。

作为她的好朋友，你决定送她这样一个字符串，但你没能找到一个。幸运的是，你可以对字符串执行两种操作：

1. 选择一个索引 $i$ 并删除字符串中的第  $i$ 个字符，这将使字符串的长度减少 $1$ 。这种操作最多可以执行 $1$ 次；

2. 选择一个索引 $i$ 并将 $s_i$ 替换为任意其他字母。

由于你很着急，你需要确定将字符串变成交替字符串所需的最少操作次数。

## 说明/提示

对于字符串 `ababa`，你可以删除第一个字符得到 `baba`，这是一个交替字符串。

对于字符串 `acdada`，你可以将前两个字符改为 `d` 和 `a` 得到 `dadada`，这是一个交替字符串。

## 样例 #1

### 输入

```
10
1
a
2
ca
3
aab
5
ababa
6
acdada
9
ejibmyyju
6
bbccbc
6
abacba
5
bcbca
5
dcbdb```

### 输出

```
1
0
1
1
2
6
2
3
1
1```

# 题解

## 作者：imfbust (赞：4)

# CF2008E

## 题意简述

对题目给出的字符串进行一下两种操作：

1. 删除一个字符（只能操作一次）
2. 将一个字符变为另一个。

求变成一个交替字符串最少操作次数。

## Solution

我们先进行分类讨论：

当 $n$ 为偶数时，由于交替字符串的长度为偶数，而只有第一个操作可以改变字符串的长度，并且只能改变一次，所以无法把一个长度为 $n$ 的字符串删成一个长度为 $n-2$ 的字符串，故只能进行第二次操作。我们可以统计奇数位和偶数位上每个字母的数量，找到最大值分别为 $maxn1, maxn2$ 答案就为 $n- maxn1- maxn2$。

当 $n$ 为奇数时，我们枚举每个位置的字符删去后变成交替字符串所需进行操作二的次数。

令 $pos$ 为此时枚举到的位置，$sumf_{i,0/1}$ 表示下标从 $1$ 到 $pos$ 字符 $i$ 在偶数位 / 奇数位的数量，$sumb_{i,0/1}$ 表示下标从 $pos+1$ 到 $n$ 字符 $i$ 在偶数位 / 奇数位的数量（由于第 $pos$ 个字符已经删去，所以后缀和无需统计）。

考虑到删去一个字符后，$pos$ 后的字符奇偶性全部改变，而之前的都不变，故令 $maxn1$ 为删去字符后偶数位上的最大值，$maxn2$ 为删去字符后奇数位上的最大值。

$maxn1= max ( maxn1,sumf_{i,0}+sumb_{i,1}), maxn2= \max (maxn2,sumf_{i,1}+sumb_{i,0})$。

统计 $maxn1+maxn2$ 的最大值，最后输出即可。

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010,M=26;
int sumf[M+5][2],sumb[M+5][2];
char s[N];
int t,n;
int main(){
    scanf("%d",&t);
    while(t--){
        memset(sumf,0,sizeof(sumf));
        memset(sumb,0,sizeof(sumb));
        int maxn1=0,maxn2=0;
        scanf("%d",&n);
        scanf("%s",s+1);
        if(!(n&1)){			//长度为偶数的情况
            for(int i=1;i<=n;i++) sumf[s[i]-'a'+1][i&1]++;
            for(int i=1;i<=M;i++) maxn1=max(maxn1,sumf[i][0]);
            for(int i=1;i<=M;i++) maxn2=max(maxn2,sumf[i][1]);
            printf("%d\n",n-maxn1-maxn2);
            continue;
        }
        for(int i=1;i<=n;i++) sumb[s[i]-'a'+1][i&1]+=1;        
        int res=0;
        for(int i=1;i<=n;i++){
            maxn1=maxn2=0;
            if(i>1) sumf[s[i-1]-'a'+1][i&1^1]++;
            sumb[s[i]-'a'+1][i&1]--;			//统计好后缀和后在枚举时逐个改变即可
            for(int j=1;j<=M;j++){
                maxn1=max(maxn1,sumf[j][0]+sumb[j][1]);
                maxn2=max(maxn2,sumf[j][1]+sumb[j][0]);
            }
            res=max(res,maxn1+maxn2);
        }
        printf("%d\n",n-res);
    }
    return 0;
}
```

---

## 作者：boluo2014 (赞：1)

这道题不怎么难！

### 思路

首先，题目说了，长度得是偶数才行。而那种删去字符的方式只能用 $1$ 次。所以，如果长度是奇数，那就用，否则不可以用。

如果是偶数，那么特别容易处理，你直接统计奇数位上出现频率最高的数和偶数位上出现频率最高的数，然后分别用长度的一半减去，加起来即可。

那现在问题就在于如何把奇数字符串转化为偶数字符串？

#### 奇数变成偶数

首先如果奇数字符串的长度是 $1$，那可以直接输出 $1$，这是很显然的。不然，要让一样的尽可能地多。然后记录以下前缀或者后缀，遍历即可。时间复杂度足够了。

### 总结

老师再见！同学再见！

---

## 作者：Super_Cube (赞：1)

# Solution

由于操作一至多执行一次，将 $n$ 分为奇偶两类讨论。

当 $n$ 为偶数时，无法执行操作一，为了最小化操作二次数，肯定希望不改变的数尽可能多，也就是保留下标分别为奇数和偶数的众数。

当 $n$ 为奇数时，枚举删掉的位置 $i$，剩下的划归为 $n$ 为偶数的情况，不过稍微麻烦点的地方在于要维护前后缀下标奇偶性的每个字母出现次数，在 $i$ 处合并左右两边信息。

# Code
```cpp
#include<bits/stdc++.h>
char s[200005];
int cnt[2][26];
int T,n,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%s",&n,s+1);
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;++i)
			++cnt[i&1][s[i]-'a'];
		if(n&1){
			static int pre[2][26];
			memset(pre,0,sizeof(pre));
			ans=0;
			for(int i=1,s1,s2;i<=n;++i){
				s1=s2=0;
				for(int j=0;j<26;++j)
					s1=std::max(s1,pre[0][j]+cnt[1][j]-pre[1][j]-((i&1)&&s[i]-'a'==j)),
					s2=std::max(s2,pre[1][j]+cnt[0][j]-pre[0][j]-(!(i&1)&&s[i]-'a'==j));
				ans=std::max(ans,s1+s2);
				++pre[i&1][s[i]-'a'];
			}
		}else
			ans=*std::max_element(cnt[0],cnt[0]+26)+*std::max_element(cnt[1],cnt[1]+26);
		printf("%d\n",n-ans);
	}
	return 0;
}

```

---

## 作者：chenxi2009 (赞：1)

# 思路

显然当字符串大小为偶数时，我们将偶数位与奇数位的字符都换成原先**分别**出现次数最多的字符就可以做到操作数最小。

当字符串大小为奇数时，因为需要枚举删除的字符所以时间复杂度达到了不能接受的 $O(n^2)$。发现其实删去一个字符对字符总出现次数的影响很小。其实际影响为：

- 自身出现次数减少；
- 在自身之后的奇数位字母变成了偶数位字母，偶数位字母变成了奇数位字母。

在枚举删去字母时，如果知道这个字母之前与之后各字母在奇偶数位上的出现次数就可以 $O(n)$ 求出答案。发现这就是字符串的相隔一个字母的每对前缀与后缀奇偶数位字母的出现次数，维护一下问题就解决了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,cnt1[26],cnt2[26],tot1[26],tot2[26],maxa,maxb,ans;//cnt 为前缀，tot 为后缀。 
char s[200001];
int main(){
	scanf("%d",&T);
	while(T --){
		memset(cnt1,0,sizeof(cnt1));
		memset(cnt2,0,sizeof(cnt2));
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			s[i] = 0;
			while(s[i] < 'a' || s[i] > 'z'){
				s[i] = getchar();
			}
		}
		if(n & 1){
			memset(tot1,0,sizeof(tot1));
			memset(tot2,0,sizeof(tot2));
			ans = n;
			for(int i = 1;i <= n;i ++){//预处理出长度为 n 的后缀 
				if(i & 1){
					tot1[s[i] - 'a'] ++;
				}
				else{
					tot2[s[i] - 'a'] ++;
				}
			}
			for(int i = 1;i <= n;i ++){
				if(i & 1){//删去这个奇数位的字母时 
					maxa = maxb = 0;
					tot1[s[i] - 'a'] --;//在后缀之中删去 s_i 
					for(int j = 0;j < 26;j ++){
						maxa = max(maxa,cnt2[j] + tot1[j]);//偶数位不用操作的位数取最大值 
						maxb = max(maxb,cnt1[j] + tot2[j]);//奇数位 
					}
					cnt1[s[i] - 'a'] ++;//在前缀之中加入 s_i 
					ans = min(ans,n - maxa - maxb);
				}
				else{//删去这个偶数位的字母时 
					tot2[s[i] - 'a'] --;
					maxa = maxb = 0;
					for(int j = 0;j < 26;j ++){
						maxa = max(maxa,cnt2[j] + tot1[j]);
						maxb = max(maxb,cnt1[j] + tot2[j]);
					}
					cnt2[s[i] - 'a'] ++;
					ans = min(ans,n - maxa - maxb);
				}
			}
			printf("%d\n",ans);
		}
		else{
			for(int i = 1;i <= (n >> 1);i ++){
				cnt1[s[(i << 1) - 1] - 'a'] ++;
				cnt2[s[i << 1] - 'a'] ++;
			}
			maxa = maxb = 0;
			for(int i = 0;i < 26;i ++){
				maxa = max(maxa,cnt1[i]);
				maxb = max(maxb,cnt2[i]);
			}
			printf("%d\n",n - maxa - maxb);
		}
	}
	return 0;
}
```

---

