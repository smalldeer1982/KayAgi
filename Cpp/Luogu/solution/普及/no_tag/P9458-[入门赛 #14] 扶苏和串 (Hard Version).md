# [入门赛 #14] 扶苏和串 (Hard Version)

## 题目背景

众所周知，每个月入门赛的字符串题都是扶苏来枚举 idea 出出来的。

## 题目描述

给定一个 01 字符串 $s$，你可以任选 $s$ 的一个非空子串，把这个子串在 $s$ 中**翻转**一次。

问你能得到字典序最小的字符串是什么？

形式化的，你可以选择一个区间 $[l, r]$ 满足 $1 \leq l \leq r \leq |s|$，构造一个串 $t$ 满足：

$$t_i = \begin{cases}s_i, &i < l \text{ 或 } i > r \\ s_{r - (i - l)}, & l \leq i \leq r\end{cases}$$

最小化字符串 $t$ 的字典序。

## 说明/提示

### 样例 1 解释

$s = \texttt{\underline{10}1}$，翻转下划线标出的子串，得到 $t = \texttt{011}$

### 样例 2 解释

$s = \texttt{00\underline{10100}}$，翻转下划线标出的子串，得到 $\texttt{0000101}$。

### 数据规模与约定

下面用 $|s|$ 表示输入字符串的长度。

- 对 $100\%$ 的数据，$1 \leq |s| \leq 3000$。$s$ 只含字符 $\texttt{0,1}$。

## 样例 #1

### 输入

```
101```

### 输出

```
011```

## 样例 #2

### 输入

```
0010100```

### 输出

```
0000101```

# 题解

## 作者：I_am_AKed_by_NOI (赞：19)

**update on 7-20** 修改了一些错别字和渲染失败的问题，同时贴上了代码并详细讲解了些细节。

### 暴力解法

观察题目，我们可以想到一个暴力。我们暴力去枚举翻转区间的左端点 $l$ 和右端点 $r$ 的位置，然后将 $l,r$ 范围内的字符进行翻转。这样计算出每一种翻转后的可能，从翻转完的字符串中取出字典序最小的输出即可。

但是复杂度并不乐观：枚举 $l$ 需要 $O(n)$，枚举 $r$ 需要 $O(n)$，翻转还需要 $O(n)$，合起来一共 $O(n^3)$，显然会炸。

由于这是入门赛，为了方便新手，这里多讲一下细节（大佬请自动跳过）：

- 如何比对两个字符串的字典序大小

我们令两个字符串为 $s1$ 和 $s2$

一部分人会说，将两个字符串遍历一遍，然后判断两个字符串同样位置上的字符的大小。

其实并不用那么麻烦，其实只需要一句话。 

``` if(s1<s2)   ```

如果成立，那么 $s1$ 的字典序更小，反之 $s2$ 更小。

- 如何对一段字符进行翻转

如果我们要翻转一个长度为 $n$ 的字符串 $s1$，显然，我们可以倒序遍历一遍 $s1$，然后存在一个新的数组里。

这里提供另外一种思路，假设翻转字符串 $luogu$。

```
luogu
ugoul
```

发现，原字符符第 $i$ 位在翻转字符串第 $n-i+1$ 位。所以可以遍历 $i$，然后进行翻转。

---------------------------------

### 正解

其实正解与暴力之间只有一个优化，那就是：**翻转的左端点其实是固定的！！！**

有一个结论：翻转的左端点必定是字符串 $s$ 中第一次出现 $1$。

通过次结论，我们就不需要暴力去枚举 $l$ 的位置，只需要 $O(n)$ 枚举 $r$，并且 $O(n)$ 进行翻转，最后找到字典序最小的即可。总复杂度 $O(n^2)$，足以通过此题。

大部分题解都没有证明这个结论，在这里我证明一下这个结论：

我们记字符串 $s$ 中第一次出现 $1$ 的位置为 $x$。$x$ 后面出现了 $0$ 的位置为 $y$（如果$x$ 后面没有出现 $0$，那么 $y=-1$）。

发现，$S_1,S_2,...,S_{x-1}$ 都为 $0$。（这里 $S_i$ 代表 $S$ 的第 $i$ 个字符）

现在分类讨论：

$(1)$：$y \ne -1$。

- 如果以 $x$ 作为左端点进行翻转，那么我们把旋转的右端点为 $y$，那么 $S_x$ 就会被改成 $0$，$S_1,S_2,...,S_{x-1}$ 依然为 $0$。

- 如果以 $x$ 左侧一点（设为 $a_1$）作为左端点进行翻转，如果右端点为 $1$，那么 $S_{a_1}$ 就会被改成 $1$.而如果以 $x$ 作为左端点进行翻转，因为 $a_1 < x$，所以 $S_{a_1}$ 显然为 $0$，$0<1$，所以这种情况不满足字典序最小。如果右端点为 $0$，类似地，也可以推出同样的结论。

- 如果 $x$ 右侧一点（设为 $a_2$）作为左端点进行翻转。不管右端点为什么， $S_x$ 不会被改变，依旧为 $1$，而如果以 $x$ 作为左端点进行翻转，$S_x=0$，$0<1$，不满足字典序最小。

综上，如果，如果 $x$ 后面有出现 $0$，那么以 $x$ 为左端点进行翻转是最优的。

$(2)$：$y = -1$

- 如果以 $x$ 作为左端点进行翻转，右端点一定是 $1$，因为 $x$ 后面没有 $0$ 的出现，所以旋转区间内的所有数都为 $1$，翻转后与原字符串相同。

- 如果以 $x$ 右侧一点（设为 $a_3$）作为左端点进行翻转，类似地，翻转后与原字符串相同。

- 如果以 $x$ 右侧一点（设为 $a_4$）作为左端点进行翻转，如果右端点（设为 $a_5$） 在 $x$ 左侧，显然的 $S_{a_4},S_{a_4+1},...S_{a_5}$ 之间所有的数都为 $0$，翻转后与原字符串相同。如果右端点（设为 $a_5$） 在 $x$ 右侧，那么 $S_{a_5}$ 一定为 $1$，翻转后 $ S_{a_4}$ 就会由 $0$ 变成 $1$，字典序比原字符串大，不是最优。

通过以上所有的证明，可以得出：翻转的左端点是字符串 $s$ 中第一次出现 $1$ 的位置最优。

### 代码

注释对上面的过程进行讲解：

```
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
string s1,s2,ans; //ans 是最后输出的答案 
int l,r; //l 是字符串中第一次出现 1 的位置，即翻转的左端点 
int main()
{
	cin>>s1;
	s2=s1; //进行备份 
	ans=s1;
  	for(int i=0;i<s1.length();i++) //遍历整个字符串，寻找第一次出现 1 的位置
	{
    	if(s1[i]=='1')
		{
    		l=i; //找到了就返回 
    		break;
    	}
	}
	for(r=l+1;r<s1.length();r++) //枚举旋转的右端点 
	{
		for(int j=l,k=r;j<=r,k>=l;j++,k--)
		{
    		s2[j]=s1[k]; //将字符串的 [l,r] 进行翻转 
    	}
    	if(s2<ans) //如果旋转之后的字符串字典序更小 
		{
    		ans=s2; //就将答案更新为字典序更小的字符串 
    	}
	}
	cout<<ans;
	return 0; //漂亮的结尾！ 
}
```

完结撒花！！

程序和思路可以带走，请把赞留下，谢谢辣！（可爱）

---

## 作者：一扶苏一 (赞：7)

# P9458

## Analysis

从左向右找到字符串第一个出现 $1$ 的位置 $p$。从后面翻转一个 $0$ 过来（如果存在）替换这个 $1$ 肯定比保留这个 $1$ 不动得到的串字典序小。这就是说，把翻转区间的左端点定在 $p$ 右侧不如定在 $p$ 或 $p$ 左侧优。

我们来证明翻转区间的左端点就是位置 $p$：  
反证法，假设答案翻转的区间是 $[l, r]$ 满足 $l < p \leq r$。设区间 $[l,r]$ 的后缀连续 $0$ 段长度是 $q$，如果翻转区间 $[l, r]$，得到的串将有 $l - 1 + q$ 个 $0$ 作为前缀；如果翻转区间 $[p, r]$，得到的串将有 $p - 1 + q$ 个 $0$ 作为前缀。后者的字典序显然比前者小。于是答案翻转的最优区间不是 $[l, r]$，矛盾，得证。

我们找到 $q$ 之后，暴力翻转右端点 $r$ 的位置，将之翻转并验证即可。时间复杂度 $O(|s|^2)$。

有一个存在问题的做法是，找到 $p$ 后面最长的连续 $0$ 段，然后把这个段的右端点作为翻转的右端点。这个做法的问题在于当存在多个最长连续 $0$ 段时，翻转哪一段是不确定的。造数据时特别卡了这个做法。

## Code

```cpp
#include <string>
#include <iostream>
#include <algorithm>

int main() {
  std::string s;
  std::cin >> s;
  if (int k = std::count(s.begin(), s.end(), '0'); k == s.size() || k == 0) {
    std::cout << s << std::endl;
    return 0;
  }
  int pos = 0;
  while (s[pos] == '0') ++pos;
  std::string ans = s, pre = s.substr(0, pos);
  for (int r = pos + 1; r <= s.size(); ++r) {
    int len = r - pos;
    auto mid = s.substr(pos, len);
    std::reverse(mid.begin(), mid.end());
    auto rest = s.substr(r);
    auto x = pre + mid + rest;
    ans = std::min(ans, x);
  }
  std::cout << ans << std::endl;
}
```

---

## 作者：Tjaweiof (赞：1)

# P9458 题解
[题目传送门](https://www.luogu.com.cn/problem/P9458)

看到题目，我们首先想到翻转后的字符串前面肯定是越多 $\texttt0$ 越好，那么我们可以轻松的想到，翻转子串的开头最好是个 $\texttt1$，而且越前面的 $\texttt1$ 越好。而翻转字串的结尾的 $\texttt0$ 越多越好，这样找到结尾。

就这么简单吗？当然不是的。如果有两个最多的 $\texttt0$ 的子串，就可以直接枚举每一种情况，选择最优解输出。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
string s, s1, ans;
int l, x, y = 0, c[3000];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	ans = s;
	l = s.size();
	for (int i = 0; i < l; i++){
		if (s[i] == '1'){
			x = i;
			break;
		}
	}
	for (int i = x; i < l; i++){
		if (s[i] == '0'){
			c[i] = c[i - 1] + 1;
		} else {
			c[i] = 0;
		}
		if (c[i] >= c[y]){
			y = i;
			s1 = s;
			int u = x, v = y;
			while (u <= v){
				swap(s1[u], s1[v]);
				u++;
				v--;
			}
			for (int j = 0; j < l; j++){
				if (s1[j] < ans[j]){
					ans = s1;
					break;
				} else if (s1[j] > ans[j]){
					break;
				}
			}
		}
	}
	cout << ans;
	return 0;
}

```
此代码时间复杂度 $O(n^2)$，空间复杂度 $O(n)$，完美过关！

---

## 作者：sz_jinzikai (赞：1)

[题目传送门](/problem/P9458)
# 思路
我们可以先找到第一个 $1$ 作为交换的起始点，然后暴力枚举后面每一个 $0$ 作为交换的结束点，最后找到字典序最小的那个即可。
# 代码
```cpp
# include <bits/stdc++.h> //万能头 
using namespace std;
string a, ans; //定义初始字符串和当前最优解字符串
size_t first_one; //记录第 1 个 1 在哪里
int main () {
	cin >> a; //输入初始字符串
	first_one = a.find ('1'); //寻找第 1 个 1
	if (first_one == string::npos) { //如果没有 1
		cout << a; //输出原字符串
		return 0; //提前结束程序
	}
	ans = a; //给当前最优解赋值
	for (size_t i = first_one + 1; i < a.size (); ++ i) //枚举字符
		if (a[i] < '1') { //如果是 0
			string t = a.substr (first_one, i - first_one + 1); //截取要交换的部分
			reverse (t.begin (), t.end ()); //交换
			ans = min (ans, a.substr (0, first_one) + t + a.substr (i + 1, a.size () - i - 1)); //更新当前最优解
		}
	cout << ans; //输出答案
	return 0; //结束程序
}
```

---

## 作者：_Emperorpenguin_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9458)
## 思路
#### $1.$ 暴力解法：
很容易想到 $O(n^3)$ 的暴力解法：

- 枚举左端点，时间复杂度为 $O(n)$；

- 枚举右端点，时间复杂度为 $O(n)$；

- 模拟翻转，时间复杂度为 $O(n)$；

但本题 $n$ 最大可达 $3000$，很明显无法通过全部数据。

#### $2.$ 正解：

本题的关键就在于找到第一个字符 $1$，并将其作为固定的翻转的左端点。

我们可以枚举第一个字符 $1$ 后的每一个字符作为右端点，然后将其翻转，并与答案数组作比较。如果翻转后的数组的字典序比答案数组的字典序更小，那么就用它替换答案数组。

正解时间复杂度为 $O(n^2)$，足以通过此题。

## Code


```cpp
#include<bits/stdc++.h>
#pragma G++ optimize(2)//手动吸氧 
using namespace std;

string s;//原字符串 
string now;//翻转后的字符串 
string ans;//答案字符串 
int first1;//记录第一个1出现的位置 
 
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin>>s;
	int n=s.length();//字符串的长度 
	ans=s;//ans设为字符串字典序的最大值 
	for(int i=0;i<n;i++)//记录第一个1出现的位置(翻转左端点） 
		if(s[i]=='1'){
			first1=i;
			break;
		} 
	for(int i=first1+1;i<=n;i++){//枚举右端点 
		now=s;//将原字符串复制到now字符串里 
		reverse(now.begin()+first1,now.begin()+i);//翻转字符串 
		ans=min(ans,now);//比较两个字符串的字典序大小，并将字典序更小的字符串置为答案 
	}
	cout<<ans; 
	return 0;
}
/*
*/


```


---

## 作者：zlt123 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9458)
## 解题思路
主要就是枚举区间，翻转后比较字典序是否小于之前的最小值（打擂台）。但是我们发现，如果串的开头全是 $0$，那么就没必要去翻转了（反转后可能会产生 $1$，与题意不符），所以可以直接确定 $l$，而 $r$ 可以直接暴力枚举，最后的算法时间复杂度为 $O(n^2)$。

话不多说，上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string str,minn;
	cin>>str;
	int len=str.length();
	minn=str;
	int n=0;
	while(str[n]=='0') n++; //减少枚举量
	for(int j=n;j<len;j++)//枚举【l，r】，其中l可以直接确定
	{	
		int i=n;
		string t;
		for(int k=0;k<i;k++)//构造新串
			t+=str[k];
		for(int k=j;k>=i;k--) 
			t+=str[k];
		for(int k=j+1;k<len;k++)
			t+=str[k];
		if(t<minn)
			minn=t;//比较
	}
	printf("%s",minn.c_str());
}
```
第一次写题解，求过。

---

## 作者：ylch (赞：0)

# 洛谷 P9458 题解

[【点击链接，查看题目】](https://www.luogu.com.cn/problem/P9458)

## 题目大意

给你一个 $01$ 字符串，随机寻找一段区间反转，使得反转后的字符串字符串最小。

## 解题思路

首先想到的是暴力枚举两个端点，后来发现 TLE，于是又想到了另一种比较巧妙的方法。

我们可以先找到第一个 $1$，将其作为左端点，然后枚举后面的每一个 $0$，将其作为右端点并反转，然后打擂台确定反转后最小的字符串。这样时间复杂度为 $\text{O}(n^2)$，足以通过本题。

对于算法的解释：

要寻找第一个 $1$ 的原因是字典序是从前往后比较的，只有把越靠前的 $1$ 换成 $0$，字典序才会更加的小。

枚举 $0$ 的原因是因为 $0$ 的字典序比 $1$ 小，反转的话肯定要把 $0$ 反转到前面来，这样才能使得到的字符串字典序较小。

这种枚举两个端点的算法有一个名字——[双指针算法](https://blog.csdn.net/annabel_cm/article/details/107352510)。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;

signed main()
{
	cin >> s;
	size_t it = s.find('1');
	if (it == string::npos)	//特判没找到
	{
		cout << s << endl;
		return 0;
	}
	string min_str = s;	//初始化为原字符串
	for (size_t i=it+1; i<s.size(); i++)
	{
		if (s[i] == '0')	//进行翻转和比较操作
		{
			string temp = s.substr(it, i-it+1);
			reverse(temp.begin(), temp.end());
			string s1 = s.substr(0, it);
			string s2 = s.substr(i+1);
			min_str = min(min_str, s1+temp+s2);
		}
	}
	cout << min_str << endl;
	return 0;
}
```

End
-------------------

管理员大大辛苦啦~

谢谢大家！

---

## 作者：Aakkosetsumussa (赞：0)

蒟蒻的第二篇题解

## 题意简述

很简单了，就是在一个 01 串中寻找一段区间翻转，使得翻转后的字符串字典序最小

## 题目分析

最简单的想法就是暴力，枚举要翻转的区间的左右端点，然后翻转再比较，但是时间复杂度 $O(n^3)$，由于 $1\leq |s|\leq 3000$，过不了这道题。

考虑优化，很简单的是，翻转区间的左端点一定是字符串中第一个出现 ```1``` 的位置，才能使得结果的字典序最小。

简单地证明一下：设字符串第一个 ```1``` 出现的位置为 $pos$，显然 $pos$ 之前的位置上都是 ```0```。设翻转区间的右端点是 $i$。

若翻转的区间为 $[p_1,i]$，其中 $p_1$ 在 $pos$ 之前，发现该区间最后一个会改变字典序的 ```1``` 在翻转后的位置会在以区间 $[pos,i]$ 翻转后的位置之前，因此以其翻转后字典序不如以后者翻转后小。

若翻转的区间为 $[p_2,i]$，其中 $p_2$ 在 $pos$ 之后，发现无论怎么翻转，在 $pos$ 位置的值不会变，还是 ```1```。而若在 $i$ 位置处是 ```0```，那么把区间 $[pos, i]$ 翻转之后，$pos$ 位置就会变成 ```0```，会有更小的字典序。

因此只要确定 $pos$ 的位置，枚举后面 ```0``` 的位置即可，时间复杂度 $O(n^2)$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
string str, ans, s, a, b; //a和b分别是pos前的部分和i后的部分
int pos;
int main() {
	cin>>str;
	ans=str, pos=str.find('1'), a=str.substr(0, pos);
	if(pos==string::npos) return cout<<str, 0; //特判全是0直接输出
	for(int i=pos+1, l; i<=str.size(); i++) {
		if(str[i-1]=='1') continue; //右端点1的不看，0的肯定比1的翻转后小
		l=i-pos, s=str.substr(pos, l), b=str.substr(i);
		reverse(s.begin(), s.end());
		ans=min(ans, a+s+b); //string可以直接比大小
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：哈哈人生 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/P9458)

## 思路
看了各位大神大佬的题解，觉得思路有点跳跃（~~这可是入门赛啊~~）。在此，我提供一种耗时但能过，并且容易理解的思路：要想字典序最小，字符串的前缀 $0$ 就得越多。所以我们要把字符串中的尽量多的零放到前面，不就可以了吗？

所以，这题朴素的暴力枚举即可：枚举翻转的区间，再用打擂台的方式求最小值（在程序中，用运算符比较字符串就可以比较字符串的字典序）。这题我们翻转区间的右端点是可以直接求出的，即第一个为 $1$ 的位置（如果不使第一个为 $1$ 的位置翻转，字典序不可能最大）。然后我们就开始从右端点加一开始枚举，枚举到字符串尾即可。

## 代码
自我感觉我的代码比大佬的代码容易懂一些，还算比较清楚。
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  string s,ans,ans2;
  int p=0;
  int main(){
      cin>>ans;
      s=ans;//拷贝字符串
      while(p<ans.size()&&ans[p]=='0')p++;//找寻右端点
      for(int i=p+2;i<=ans.size();i++){//枚举左端点
         ans2=s;
         reverse(ans2.begin()+p,ans2.begin()+i);//翻转函数
         ans=min(ans,ans2);//用函数比较字典序
      }
      cout<<ans;//输出
      return 0;
  }
```
请读者诚信粘题解，遵守洛谷规则，另外，点个赞呗~。

---

## 作者：InversionShadow (赞：0)

## P9458 [入门赛 #14] 扶苏和串 (Hard Version) 题解

首先先放个结论：$l$ 是 $s$ 中第一个出现 `1` 的位置。

可以证明，$l$ 一定是 `1`，否则翻转过来字典序一定不优，所以我们找到第一个 `1` 的位置，剩下就可以暴力求解了。

确定了左端点，我们就可以 $O(n)$ 枚举 $r$ 的位置，$O(n)$ 交换 $l \sim r$ 上的字符，进行比较，所以总时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 100;

string s, b, a;

int main() {
  cin >> s;
  b = a = s;
  int n = s.size();
  int l = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      l = i;
      break;
    }
  }
  for (int i = l + 1; i < n; i++) {
    for (int j = l, k = i; j <= i, k >= l; j++, k--) {
      b[j] = s[k];
    }
    if (b < a) {
      a = b;
    }
  }
  cout << a;
  return 0;
}
```

---

## 作者：流光萤影 (赞：0)

**前言：本题解使用语言：C++14 O2**



------------

**正文：**


## 基本思路（一）：

**分析**：如果 $s _ l = \texttt{0}$，那么翻转 $s _ {[l,r]}$ 必然不优，这样翻转可能将后面的 $\texttt{1}$ 翻转到前面从而使字典序变大。

用本题的样例 #1 举例：$s = \texttt{101}$，翻转 $s _ {[1,2]}$ 后 $s = \texttt{110}$，字典序变大，不符合题意。

而如果 $s _ l = \texttt{1}$，除非 $s _ {[l,|s|]}$ 全是 $\texttt{1}$，否则一定可以将后面的 $\texttt{0}$ 翻转到前面。只要枚举 $[l,r]$ 的范围即可。

**那么，核心结论就得出了：如果 $s _ l = \texttt{1}$，就翻转 $s _ {[l,r]}(1 \leq l \leq r \leq |s|)$。**

注：其实 $l < r$ 就行了，可以节约一些被浪费了的时间。

**时间复杂度**：查找 $\texttt{1}$ 的时间复杂度为 $O(|s|)$，每次翻转时间复杂度最大为 $O(|s|)$，**总时间复杂度为 $O(|s| ^ 2)$**。

------------


## 2.代码实现（二）：

**翻转功能实现：**

```cpp
reverse(s.begin()+i,s.begin()+j); //i,j即l,r
```

**比较字典序功能实现：**

```cpp
a = min(a,tmp); //tmp为此次翻转后的字符串t，a为answer
```

**进一步推出代码核心部分：**

```cpp
for(int i = 0;i <= s.length();i++) //遍历找'1'
{
	if(s[i] == '1')
	{
		for(int j = i;j <= s.length();j++) //枚举r
		{
			tmp = s;
        reverse(tmp.begin()+i,tmp.begin()+j);
			a = min(a,tmp);
		}
	}
}
```

------------

**AC 代码：**

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
using namespace std;
string s,a,tmp;
int main()
{
	cin >> s;
	a = s;
	for(int i = 0;i <= s.length();i++)
	{
		if(s[i] == '1')
		{
			for(int j = i;j <= s.length();j++)
			{
				tmp = s;
				reverse(tmp.begin()+i,tmp.begin()+j);
				a = min(a,tmp);
			}
		}
	}
	cout << a;
}
```


---

## 作者：_O_v_O_ (赞：0)

前置知识：[B3810](https://www.luogu.com.cn/problem/B3810)。

首先放出一条结论：$s_l$ 一定是从前往后第一个满足条件的 $s_l$。

证明：如果 $s_l$ 是 $0$，那么翻转后的字符串字典序一定比 $s_l$ 为 $1$ 的高（假设 $s_r$ 固定）。

对于“从前往后第一个满足条件的 $s_l$”的推导过程，其实更简单：因为这样能让字符串最后有尽可能多的 $0$，字典序尽可能小。

有了这条结论，就简单多了，前面那题是用 $O(|s|^3)$ 的方法，其中有一层循环是枚举 $l$ 的，可有了这个结论，时间直接降到 $O(|s|^2)$，能过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

string s,mn,ss;  //mn 为字典序排最小的字符串，开始应初始化为 s。

signed main(){
	cin>>s;
	int l=0,ll=s.size();
	mn=s;
	for(;;l++){  //枚举 l。
		if(s[l]=='1') break;
	}
	for(int i=l+1;i<ll;i++){
		ss=s;
		for(int nowl=l,nowr=i;nowl<=i,nowr>=l;nowl++,nowr--){  //翻转。
			ss[nowl]=s[nowr];
		}
		if(ss<mn) mn=ss;
	}
	cout<<mn;
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：0)

## 题意

给你一个字符串，你可以翻转其中一段，得到的求字典序最小的串。

## 解析

显然，我们翻转的起点应该是该串中第一个 ```1``` 的位置，如果起点在后面的话，这个 ```1``` 就还在原来的位置，显然不如其它情况优。

确定了左端点，我们可以 $O(n)$ 枚举右端点，暴力得出每一个可能得串，然后比较，复杂度是 $O(n^2)$，对于 $n\le 3000$ 的数据显然是足够了。

## 核心代码
```cpp
string ask(int r)//翻转
{
    string st;
    for(int i=0;i<n;i++)
    {
        if(i<l)st.push_back(str[i]);
        else if(i<=r)
        {
            st.push_back(str[r-i+l]);
        }
        else st.push_back(str[i]);
    }
    return st;
}
```

```cpp
    for(int i=0;i<n;i++)
    {
        if(str[i]=='1')
        {
            l=i;
            break;
        }
    }
    string ans="2";
    for(int i=l+1;i<n;i++)
    {
        ans=min(ans,ask(i));
    }
    cout<<ans;
```

可以看见主函数的部分非常的暴力啊，并不用去想线性的贪心而且可能是错的。

---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/P9458)

首先思考最朴素的算法：

$\text{O}(n^2\text)$ 枚举 $l,r$，$\text{O}(n)$ 翻转子串，$\text{O}(n)$ 判断大小，合起来是 $\text{O}(n^2(n+n))=\text{O}(n^3)$ 的时间，显然过不了。

想办法消去一层循环。

再观察一下：

若 $s_l=0$ 且 $s_r=1$，那么翻转之后一定会让字符串变得更大。

若 $s_l=0$ 且 $s_r=0$，那么翻转 $[l,r]$ 相当于翻转 $[l+1,r-1]$。

综上，$s_l=1$。

那 $1$ 也可能有很多个，不可能全部枚举。

继续观察发现，若 $\exists1\leq l_0<l,s_{l_0}=1$，那么不论 $l,r$ 为多少，都不会比翻转 $[l_0,r]$ 更优。

那我们就可以确定 $l$ 一定为第一个 $1$ 所在的位置，时间降低为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void min(string&a,string b){if(b<a) a=b;}
string s;int n,l;
int main(){
	cin>>s;n=s.size();
	while(l<n&&s[l]=='0') ++l;
	if(l>n) cout<<s<<endl;
	else{
		string t(s.substr(0,l)),ans(s);
		for(int r(l);r<n;++r){
			string x(s.substr(l,r-l+1));
			string y(s.substr(r+1));
			for(int i(0);i<x.size()/2;++i)
				swap(x[i],x[x.size()-i-1]);
			min(ans,t+x+y);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_Glassy_Sky_ (赞：0)

# P9458 [入门赛 #14] 扶苏和串 (Hard Version)题解

[题目](https://www.luogu.com.cn/problem/P9458)


## 1、思路
字符串前面的 $0$ 不用管，因为如果把它反过来字符串就变大了，所以我们要找到字符串从左起第一次出现的 $1$。可以直接暴力搜索一遍，也可以使用字符串自带的函数。

第一种方法暴力搜索，也就是从 $0$ 号为开始，一直扫到字符串结束，如果出现了 $1$，那就标记一下位置，结束循环；如果扫到最后还没有发现 $1$，那就直接输出字符串，因为这时候字符串里面全是 $0$，已经是最小的情况了。

具体如下：
```cpp
for(int i = 0; i < s.size(); i ++)
	{
		if(s[i] == '1')
		{
			k = i;//标记第一个'1'出现的位置。 
			break;
		}	
		if(i == s.size() - 1)//条件判断是不是到最后一次循环了，如果到了并且是'1'，就执行第一个判断，否则就执行这个判断，因为这个时候字符串里全是'0'，已经是最小状态 
		{
			cout << s;
			return 0;//直接结束 
		}
	}
```
第二种是用 c++ 自带的 find 函数，具体用法如下：

find 函数会返回要寻找的部分第一次出现的位置，没有会返回 $-1$。
```cpp
int k = s.find('1');//从字符串里寻找'1' 
	if(k == -1)//找不到'1'
	{
		cout << s;
		return 0;
	} 
```

然后从 $1$ 第一次出现的位置开始，往后去尝试，每尝试一段，就翻转一下，与原来的比较大小，选择较小者：
```cpp
reverse(cnt.begin() + k, cnt.begin() + i);//翻转这一段 
ans = min(ans, cnt);//比较大小
```
## 2、代码
代码的话就是把以上所讲的内容整合一下，再多定义几个变量就可以了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{   
	int k = 0;
        string s, ans, cnt;
	cin >> s;
	ans = cnt = s; 
        k = s.find('1');//从字符串里寻找'1' 
	if(k == -1)//找不到'1'
	{
		cout << s;
		return 0;
	} 
        for(int i = k + 1; i <= s.size(); i ++)
	{
		cnt = s;
        reverse(cnt.begin() + k, cnt.begin() + i);//翻转这一段 
        ans = min(ans, cnt);//与原来的比较大小（字符串是可以互相比较的） 
        }
        cout << ans << '\n';
        return 0;
}
```
~~本人第一篇题解，希望管理员大大给过~~

---

## 作者：JackMerryYoung (赞：0)

# 前言

赛时一发过好耶。

# 正文

证伪大家觉得好像对的贪心：

两种局部最优想法：一种是找到第一个 $1$ 和前面有连续的 $0$ 最多 $0$ 的位置，一种是找的第一个 $1$ 和最后一个 $0$。

显然第一种是错的，有可能再包括一位 $1$ 而且其后面的 $0$ 更多，翻转的时候使得原来的一更加后面，但是再包括一位的 $1$ 翻转后比原来不包括这一位直接翻转的第一个 $1$ 的现在位置还要后面（可以构造）。第二种可能翻转过来产生原来第一个 $1$ 的后一位是 $1$ 的极端情况，显然不优。

所以这题只需暴力枚举翻转的段末尾位置 $0$ 即可。而且是 $\mathcal{O}(|s|^2)$ 不会超时的。

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rint register ll

string s, ans;

string string_reverse(string x)
{
    return string(x.rbegin(), x.rend());
}

signed main()
{
    cin >> s;
    ll startpos = -1ll;
    for(int i = 1; i <= 1000; ++ i) ans += "1111";
    for(ll i = 0; i < s.length(); ++ i) 
    {
        if(s[i] == '1' && startpos == -1ll) startpos = i;
        if(s[i] == '0' && startpos != -1ll) { string tmps = s.substr(0ll, max(0ll, startpos)) + string_reverse(s.substr(startpos, i - startpos + 1ll)) + s.substr(i + 1ll, s.length() - i);  ans = min(ans, tmps); }
    }

    cout << ans << endl;
    return 0;
}
```

# 后言

警钟长鸣：考场上千万不要写自己 yy 并且觉得“很”对的的贪心。

赛后回复了不止五个帖子都是贪心挂掉的。

---

