# 题目信息

# Necklace Assembly

## 题目描述

The store sells $ n $ beads. The color of each bead is described by a lowercase letter of the English alphabet ("a"–"z"). You want to buy some beads to assemble a necklace from them.

A necklace is a set of beads connected in a circle.

For example, if the store sells beads "a", "b", "c", "a", "c", "c", then you can assemble the following necklaces (these are not all possible options):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/d2ddac43ecb91517adf034c4a5c0862106e5b4e4.png)And the following necklaces cannot be assembled from beads sold in the store:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/509baa50603d3d471878b58a508e7ec9dac1674b.png)The first necklace cannot be assembled because it has three beads "a" (of the two available). The second necklace cannot be assembled because it contains a bead "d", which is not sold in the store.We call a necklace $ k $ -beautiful if, when it is turned clockwise by $ k $ beads, the necklace remains unchanged. For example, here is a sequence of three turns of a necklace.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/2f3c78fa3723939cbe420518274f88aa30a08005.png) As you can see, this necklace is, for example, $ 3 $ -beautiful, $ 6 $ -beautiful, $ 9 $ -beautiful, and so on, but it is not $ 1 $ -beautiful or $ 2 $ -beautiful.In particular, a necklace of length $ 1 $ is $ k $ -beautiful for any integer $ k $ . A necklace that consists of beads of the same color is also beautiful for any $ k $ .

You are given the integers $ n $ and $ k $ , and also the string $ s $ containing $ n $ lowercase letters of the English alphabet — each letter defines a bead in the store. You can buy any subset of beads and connect them in any order. Find the maximum length of a $ k $ -beautiful necklace you can assemble.

## 说明/提示

The first test case is explained in the statement.

In the second test case, a $ 6 $ -beautiful necklace can be assembled from all the letters.

In the third test case, a $ 1000 $ -beautiful necklace can be assembled, for example, from beads "abzyo".

## 样例 #1

### 输入

```
6
6 3
abcbac
3 6
aaa
7 1000
abczgyo
5 4
ababa
20 10
aaebdbabdbbddaadaadc
20 5
ecbedececacbcbccbdec```

### 输出

```
6
3
5
4
15
10```

# AI分析结果

### 题目中文重写
# 项链组装

## 题目描述
商店出售 $n$ 颗珠子。每颗珠子的颜色由一个小写英文字母（"a" - "z"）描述。你想购买一些珠子来组装一条项链。

项链是一组连接成一个圆圈的珠子。

例如，如果商店出售珠子 "a"、"b"、"c"、"a"、"c"、"c"，那么你可以组装出以下项链（这些不是所有可能的选项）：
![示例图片1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/d2ddac43ecb91517adf034c4a5c0862106e5b4e4.png)
而以下项链无法用商店出售的珠子组装：
![示例图片2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/509baa50603d3d471878b58a508e7ec9dac1674b.png)
第一条项链无法组装，因为它有三颗 "a" 珠子（而商店只有两颗）。第二条项链无法组装，因为它包含一颗商店没有出售的 "d" 珠子。

我们称一条项链是 $k$ - 美丽的，如果将它顺时针旋转 $k$ 颗珠子后，项链保持不变。例如，以下是一条项链旋转三次的序列。
![示例图片3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1367E/2f3c78fa3723939cbe420518274f88aa30a08005.png)
如你所见，这条项链例如是 $3$ - 美丽的、$6$ - 美丽的、$9$ - 美丽的等等，但它不是 $1$ - 美丽的或 $2$ - 美丽的。

特别地，长度为 $1$ 的项链对于任何整数 $k$ 都是 $k$ - 美丽的。由相同颜色珠子组成的项链对于任何 $k$ 也是美丽的。

给定整数 $n$ 和 $k$，以及包含 $n$ 个小写英文字母的字符串 $s$，每个字母代表商店中的一颗珠子。你可以购买珠子的任何子集并以任何顺序连接它们。找出你可以组装的 $k$ - 美丽项链的最大长度。

## 说明/提示
第一个测试用例在题目描述中已解释。

在第二个测试用例中，可以用所有字母组装出一条 $6$ - 美丽的项链。

在第三个测试用例中，可以组装出一条 $1000$ - 美丽的项链，例如由珠子 "abzyo" 组成。

## 样例 #1
### 输入
```
6
6 3
abcbac
3 6
aaa
7 1000
abczgyo
5 4
ababa
20 10
aaebdbabdbbddaadaadc
20 5
ecbedececacbcbccbdec
```
### 输出
```
6
3
5
4
15
10
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是围绕枚举答案来展开，判断不同长度的项链是否能满足 $k$ - 美丽的条件，从而找出最大长度。各题解的差异主要在于枚举和判断的具体方式。
- **思路对比**：大部分题解通过枚举项链长度，利用 $\gcd$ 计算块长和块数，判断字符数量是否足够；F_Mu 的题解枚举 $k$ 的因子，利用二分查找最大节数；_edge_ 的题解先通过暴力连边找连通块，再优化为利用裴蜀定理计算连通块个数。
- **算法要点**：关键在于理解 $k$ - 美丽项链的性质，即项链由多个相同的块组成，块长是 $k$ 的因数，通过 $\gcd$ 计算相关参数。
- **解决难点**：主要难点在于如何高效判断某个长度的项链是否能组装出来，不同题解采用了不同的方法，如直接计算字符贡献、二分查找、贪心匹配等。

### 所选题解
- **Tx_Lcy（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接枚举答案，利用 $\gcd$ 计算块长和块数，通过比较字符贡献和块长判断是否可行。
- **FireFy（4星）**
    - **关键亮点**：对题意进行简化，便于理解，同样采用枚举答案的方法，计算段数和段长，判断是否满足条件。
- **yr409892525（4星）**
    - **关键亮点**：从大到小枚举答案，利用 $\gcd$ 计算块数，判断字符贡献是否合法，第一个合法答案即为最大答案。

### 重点代码
#### Tx_Lcy 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=2e3+10;
int a[30];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while (t--){
        memset(a,0,sizeof a);
        int n,k;string s;cin>>n>>k>>s;
        s=" "+s;int ans=0;
        for (int i=1;i<=n;++i) ++a[s[i]-'a'];
        for (int i=1;i<=n;++i){
            int len=i/__gcd(i,k),sum=0;
            for (int j=0;j<26;++j) sum+=a[j]/len;
            if (sum>=__gcd(i,k)) ans=max(ans,i);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
**核心实现思想**：枚举项链长度 $i$，计算块长为 $\gcd(i,k)$，块数为 $i / \gcd(i,k)$，统计每个字符在每个块中的数量，若总数大于等于块长，则更新答案。

#### FireFy 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
char c[2024];
int book[30];
int gcd(int n,int m)
{
	if(n%m==0) return m;
	else return gcd(m,n%m);
}
int main()
{
	int T,i,j,n,m,k,ans=0;
	cin>>T;
	while(T--)
	{
		ans=0;
		for(i=1;i<=30;i++) book[i]=0;
		cin>>n>>k;
		for(i=1;i<=n;i++)
		{
			cin>>c[i];
			book[c[i]-'a'+1]++;
		}
		for(i=1;i<=n;i++)
		{
			int len=gcd(max(i,k),min(i,k)),num=i/len,sum=0;
			for(j=1;j<=26;j++) sum+=book[j]/num;
			if(sum>=len) ans=i; 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
**核心实现思想**：枚举项链长度 $i$，计算段长为 $\gcd(i,k)$，段数为 $i / \gcd(i,k)$，统计每个字符在每个段中的数量，若总数大于等于段长，则更新答案。

#### yr409892525 的题解
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,inf=1e18;
int a[N];
int gcd(int x,int y){
	return ((y==0)?x:gcd(y,x%y));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		string s;
		cin>>s;
		for(int i=0;i<26;i++) a[i]=0;
		for(int i=0;i<n;i++){
			a[s[i]-'a']++; 
		} 
		for(int i=n;i>=1;i--){
			int x=gcd(i,m);
			int sum=0;
			for(int j=0;j<26;j++){
				sum+=a[j]*x/i;
			}
			if(sum>=x){
				cout<<i<<"\n";
				break;
			}
		}
	}
	return 0;
}
```
**核心实现思想**：从大到小枚举项链长度 $i$，计算块数为 $\gcd(i,k)$，统计每个字符对答案的贡献，若总数大于等于块数，则输出该长度并结束循环。

### 最优关键思路或技巧
- 利用 $\gcd$ 计算块长和块数，将问题转化为判断字符数量是否足够填充这些块。
- 枚举答案，通过比较字符贡献和块长来判断可行性。

### 拓展思路
同类型题可能会改变项链的旋转规则或珠子的限制条件，但核心思路仍然是围绕枚举和判断可行性展开。类似算法套路包括枚举可能的结果，利用数学性质简化判断过程。

### 推荐题目
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1077 摆花](https://www.luogu.com.cn/problem/P1077)

### 个人心得
- **AlexandreLea**：学了多年 OI，感觉对个人能力提升和升学帮助不大，打算回去当算法爱好者。感悟工匠精神虽不以成功为旨归，但能为成功铺就道路。 

---
处理用时：64.57秒