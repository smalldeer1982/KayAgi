# Minimum Sum

## 题目描述

Petya 有一个长度为n的正整数序列 $a_{1},a_{2},...,a_{n}$。他的朋友Vasya 想要捉弄他，Vasya用一个字母替换了Petya 的号码中的所有数字。

他用小写字母‘a’到‘j’中的一个字母替换了所有数字 0，用另一个字母替换了所有 1，依次类推。对于不同的两个数字，Vasya 用‘a’到‘j’中不同的字母。

你的任务是还原 Petya 的序列。还原得到的数字应是没有前导零（数字开头没有零）的正整数。由于可能有多种方式实现，所以要求恢复后的序列总和最小。保证初始时序列中数字没有前导零。

## 样例 #1

### 输入

```
3
ab
de
aj
```

### 输出

```
47
```

## 样例 #2

### 输入

```
5
abcdef
ghij
bdef
accbd
g
```

### 输出

```
136542
```

## 样例 #3

### 输入

```
3
aa
jj
aa
```

### 输出

```
44
```

# 题解

## 作者：chengni (赞：3)

因为一共只有十个字母（数字），所以比较简单。

我们可以计算出每一个字母所代表的数字一共出现了多少次，一位上一次，十位上十次，依次类推。

我们求的是总和，所以我们需要让每个数字乘上它出现的次数最小。

我们将每一个字母出现的次数从大到小排序，最多次数的那个字母代表0，然后1,2,3......

需要注意的是，0是不能作为开头字母的，需要判断一下。

然后就做出来了

代码

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	char ch=getchar();int x=0,f=1;
	while(ch>'9' || ch<'0'){
        if(ch=='-') f=-1;
	    ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

char c[10000000]; 

int pos(int x){
	int ans=1;
	for(int i=1;i<=x;i++){
		ans*=10;
	}
	return ans;
}


struct node {
	int a,b;
}t[100000];

bool cmp(node x,node y){
	return x.a>y.a;
}

int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		cin>>c;
		int l=strlen(c);
		for(int j=0;j<l;j++){
			t[c[j]-'a'+1].a+=pos(l-j-1);
			if(j==0) t[c[j]-'a'+1].b=1;//判断能否为0
		}
	}
	sort(t+1,t+11,cmp);//按出现次数排序
	for(int i=1;i<=10;i++){//选一个可以为0的数
		if(t[i].b==0 && t[i].a!=0){
			t[i].a=0;
			break;
		}
	}
	int ans=0,sum=1;
	for(int i=1;i<=10;i++){
		if(t[i].a!=0){
			ans+=t[i].a*sum;//出现次数*数字
			sum++;
		}
	}
	cout<<ans<<endl;
} 
```

---

## 作者：codeLJH114514 (赞：2)

[$\colorbox{#3498db}{\color{#fff}返回题目}$](https://www.luogu.com.cn/problem/CF910C)

## 题目描述

给你 $n$ 和 $n$ 个字符串 $s_1, s_2, s_3, s_4, \cdots, s_n$，每一个字符串都是一个数字，用 $0 \sim 9$ 替换 $a \sim j$，使得字符串们的和最小。

## 解题思路

第一步，求出每一个字母对答案的贡献，如在 $n \to 2$，$s \to \{abc, abcd\}$ 中，$a$ 的贡献即为 $100 + 1000 = 1100$，$b$ 的贡献即为 $10 + 100 = 110$，依次类推。

第二步，因为有的字母不能为 $0$（如在前一个例子中，$a$ 就不能为 $0$），所以我们在统计贡献时还要存该字母能不能为 $0$，并在最后找出能为 $0$ 的贡献最大的字母，将它替换为 $0$ 即可。例如在 $n \to 3$，$s \to \{ab, de, aj\}$ 中，要替换成 $0$ 的就是 $b$ 或 $e$ 或 $j$，因为他们不在最高位上（只有这几个能选）。

第三步，将其余字母按照贡献排序，贡献越大所对应的数字就应该越小，因为我们要求的是最小的和。 例如在 $n \to 3$，$s \to \{ab, de, aj\}$ 中，$a$ 就应替换为 $1$ 因为它的贡献最大，$d$ 就应该替换为 $2$，以此类推。

第四步，求出每一个字母对总和的贡献，直接用替换的数字乘以对答案的贡献即可。

## 完整代码

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
int n;
string s;
class Node{
    public:
        int v, k; // 该字母要替换为的数字和对答案的贡献。
        bool t; // 该字母是否可以为0。（即是否在最高位上出现过。）
        char ch; // 字母的字符。（调试时用的。）
        bool operator<(const Node& n) const& {
            return k > n.k;
        } // 自定义小于号。
} d[12]; // 自定义结构体来存每一个字母的情况。
int main() {
    cin >> n;
    for (int i = 1; i <= 10; i++) d[i].ch = i + 'a' - 1; // 将该字母的字符初始化。
    for (int i = 1; i <= n; i++) {
        cin >> s;
        d[s[0] - 'a' + 1].t = true;
        for (int j = 0; j < s.size(); j++)
            d[s[j] - 'a' + 1].k += pow(10, s.size() - j - 1);
    }
    sort(d + 1, d + 10 + 1);
    int zero = 0;
    for (int i = 1; i <= 10; i++) {
        if (not d[i].t) { // 因为已经排序所以第一个可以为0的肯定是对答案的贡献最大的。
            zero = i;
            break;
        }
    }
    for (int i = 1; i <= 10; i++) d[i].v = -1; // 将v赋值为-1即为还未确定要替换的数字。
    d[zero].v = 0; // 将替换的数字赋值0。
    int cnt = 1;
    for (int i = 1; i <= 10; i++)
        if (d[i].v == -1)
            d[i].v = cnt++; // 依次确定要替换的数字。
    int ans = 0;
    for (int i = 1; i <= 10; i++)
        ans += d[i].v * d[i].k; // 累加ans。
    /*
    for (int i = 1; i <= 10; i++)
    	cout << d[i].ch << " " << d[i].k << " " << d[i].v << " " << d[i].t << "\n";
    */
    cout << ans; // 输出。
    return 0;
}
```

---

## 作者：hulean (赞：1)

当时看到这题一脸懵逼，莫名想到了复杂度为O(10000000000*n)的算法，然而肯定会超时~~(废话)~~

算法楼上楼下都说的很清楚了

很明显这题是要用每个字母的权值进行排序。然后依次进行赋值。

$\color{red}\text{注意:不能有前导零，所以要进行特判}$

看代码吧:

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[1100];
int n;
struct Node
{
    int num,sum;//num表示该数组下标表示的字母，因为排序后会打乱，所以要先记录一下
    bool first;//是否首字母
}word[11];//分别表示a,b,c,d,e,f,g,h,i,j
int p[11];//表示a~j分别代表的
bool vis[11];//表示0~9这9个数是否用过
inline bool cmp(Node u,Node v)//按权值排序
{
    return u.sum>v.sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=10;i++)word[i].num=i;//先赋值
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        word[s[i][0]-'a'+1].first=1;//首字母
        for(int j=0;j<s[i].size();j++)
        {
            word[s[i][j]-'a'+1].sum+=pow(10,s[i].size()-j);//加权值
        }
    }
    sort(word+1,word+11,cmp);//排序
    /*for(int i=1;i<=10;i++)
    {
        cout<<word[i].num<<" "<<word[i].sum<<" "<<word[i].first<<endl;
    }*/
    for(int i=1;i<=10;i++)
    {
        if(word[i].first)//如果它是首字母
        {
            for(int j=1;j<=9;j++)if(!vis[j])//从1~9中选一个
            {
                vis[j]=1;//标记为用过
                p[word[i].num]=j;//这时记录的东西就很有用了
                break;
            }
        }
        else
        {
            for(int j=0;j<=9;j++)if(!vis[j])//如果不是首字母，那就在0~9中选择
            {
                vis[j]=1;//标记为用过
                p[word[i].num]=j;
                break;
            }
        }
    }
    /*for(int i=1;i<=10;i++)cout<<p[i]<<" ";
    cout<<endl;*/
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int cnt=0;
        for(int j=0;j<s[i].size();j++)
        {
            cnt=cnt*10+p[s[i][j]-'a'+1];//计算当前字符串的值
        }
        ans+=cnt;//总答案加上
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：贞白铁战逸 (赞：1)



------------
    **这是蒟蒻我的第一篇题解，希望大家多多支持，不足之处望指出。
    我们知道每个字母位数越高，其所代的值应越小。
    所以我给每个字母在结构体中定义了一个优先度。其随着位数增高而以10递增（十进制）。
    然后就以优先度排序，这里注意，放在首位的字母不能为0，要特别标记。
        如第一个测试数据
    3
    ab
    de
    aj
    a的优先度为10+10=20；
    d的优先度为10
    b，e，j优先度都为1
    但因为a和d在首位，所以只能为1，2
    b，e，j则为0,3,4；
    所以10+23+14=47.
    数据不大，用long long 就可以过。
    以下是代码：**
   

------------

    ```cpp**
     include <cstdio>
     include <cmath>
     include <cstring>
     include <iostream>
     include <algorithm>
     using namespace std;
     long long n, ss, zs;
     int r[27]={0};
     string s[100000];

     struct node
     {
      long long yxd;  //优先度
      char zm;  //对应字母
      bool qd;  //记录是否会为首位
      node(long long yxd1 = 0, char zm1 = 0, bool qd1 = 0 )
      {yxd = yxd1; zm = zm1 ; qd = qd1;}
      }a[100];

     int t[10] = {0};

     bool cmp(node x, node y)
     {
         return x.yxd > y.yxd; //按优先度排序
     }

     int main()
     {
         int i, j, k, l;
         scanf ("%d", &n);
         for (i = 1; i <= n; i++）
             cin >> s[i]；
         for (i = 1; i <= 26; i++)
             a[i].zm = char(i+96);
         for (i = 1; i <= n; i++)
         {
             l = s[i].size()-1;
             int p = 1;      
             for (j = l; j >= 0; j--)    
             {        
                 a[s[i][j]-96].yxd += p;  //计算优先度           
                 p *= 10;  //位数越高，优先度越高            
                 if (j == 0) a[s[i][j]-96].qd = 1;  //记录首位的数           
             }       
     }   
     sort(a+1, a+27, cmp);   //按优先度排序
     for (i = 1; i <= 26; i++)   //算出个字母所代的数
     {
          for (j = 0 ;j <= 9; j++) 
             if (j == 0 && a[i].qd == 1 || t[j] == 1)
                 continue；
             else {
                 r[a[i].zm-96] = j;
                 t[j] = 1;
                 break;
             }
     }

     for (i = 1; i <= n; i++)   //计算各加数
     {
         ss = 0;
         for (j = 0; j <= s[i].size()-1; j++)
         ss = ss*10 + r[s[i][j]-96];
         zs += ss;   //相加
     }
     printf ("%lld", zs);
     }
    ```

---

## 作者：1qaz234567pzy (赞：0)



~~最优解竟是我自己~~

这题不难。~~然鹅我交了三遍才过~~



## 思路

输入每个字符串的时候统计每个字母出现的次数，即计算总和的时候要累加的次数，在（从后往前）第 $k$ 个字母的出现次数就累加上 $10^{k-1}$，用一个数组保存下来。因为题目要求总和最小，所以尽可能让出现次数**越多**的字母代表的数字尽可能**小**。又由于**不能有前导零**，所以标记一下每个字符串的第一个字母。随后跑一边 `sort`，从大到小排序，找到出现**次数最多的且没被标记**的字母，将其的出现次数设为**零**（就是让其代表 $0$）。最后在跑一次 `sort`，从大到小排序，然后最后让出现次数越多的数代表越小的数（从 $1$ 到 $9$），计算总和就可以了~



------------

代码如下：
```cpp

#include<bits/stdc++.h>
using namespace std;
pair<int ,bool> shu[100];//pair的first存出现次数，second存能否为0
long long sum;
int n,flag=-1;
string a;
int p10pow(int n)//10的n次幂
{
    int  aa=1;
    for(int rr=1;rr<=n;rr++)
    {
        aa*=10;
    }
    return aa;
}
bool cmp(pair<int,bool> a,pair<int,bool> b)//排序规则
{
    return a.first>b.first;
}
int main()
{
    cin>>n;
    for(int qq=1;qq<=n;qq++)
    {
        cin>>a;
        shu[a[0]-'a'].second=1;//标记第一个字母
        for(int ww=a.size()-1;ww>=0;ww--)
        {
            shu[a[ww]-'a'].first+=p10pow(a.size()-ww-1);//计算出现次数
        }
    }
    sort(shu,shu+10,cmp);//排序
    for(int dd=0;dd<10;dd++)
    {
   
        if(!shu[dd].second&&shu[dd].first)//找到出现次数最多的没被标记的字母
        {
            flag=dd;
            shu[dd].first=0;
            break;
        }
    }
	  sort(shu,shu+10,cmp);	//再次排序
    for(int dd=0;dd<10;dd++)
    {
        sum+=shu[dd].first*(dd+1);
    }
    cout<<sum;
    return 0;//完结撒花~~~
}

```

------------
不要抄代码哟~

[AC记录](https://www.luogu.com.cn/record/119545730)













---

## 作者：_frog (赞：0)

# CF910C Minimum Sum 题解
## 题意简述
+ 有 $n$ 个字符串 $s_1,s_2,\cdots,s_n$，每个字符串中的字符都为小写字母‘a’到‘j’。
+ 现在要用‘0’到‘9’替换小写字母‘a’到‘j’，且每个字符串的第一个字符不能为‘0’。
+ 求替换后字符串表示的数和的最小值。
+ $1\le n\le 1000$，$1\le\text{字符串长度}\le 6$。
## 题目分析
$\overline{abcdef}=f+10e+10^2d+10^3c+10^4b+10^5a$，所以对于一个正整数，一个数字在小数点左侧的第 $i$ 位，它的权重就是 $10^{i-1}$。

同样，如字母‘a’在字符串倒数第二位上（十位），则字母‘a’的权重就是 $10$；如字母‘a’在字符串倒数第五位上（万位），则字母‘a’的权重就是 $10^4$。

那么，如字符 $x$ 被 $v_x$ 所替换，字符 $x$ 在所有字符串中权重之和为 $w_x$，所有字符串表示的数的和应为 $\sum_{x=\text{‘a’}}^{\text{‘j’}}{}v_x\times w_x$。

而要使所有字符串表示的数的和最小，权重小的字符应尽量被大的数字所替换。

但还要特判前导零：由于 $0$ 是最小的数字，所以得替换权重尽量大的字符。

于是我们可以遍历字符（权重从大到小），如所有字符串的开头都不是该字符，则 $0$ 就替换此字符。

随后我们遍历字符（权重从小到大），并用从大到小的数字替换，再算出答案。

流程：
1. 输入，并计算字符权重，记录不能为‘0’的字符。（$O(\text{字符串长度}\times n)$）
2. 排序。（$O(10\times\log(10))$=$O(1)$）
3. 特判前导零。（$O(10)$=$O(1)$）
4. 计算，输出。（$O(10)$=$O(1)$）

时间复杂度：$O(\text{字符串长度}\times n)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string str[1010];
bool flg[11];
ll n, t[11], ans, zero_ind;
struct Node {//运用结构体排序
	bool can_be_0;//可以为0
	ll val;//权重
	char name;//字符
} a[11];
bool cmp(Node x, Node y) {
	if (x.val != y.val)return x.val < y.val; //权重小的排在前
	return x.name < y.name;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (ll i = 0; i < n; i++) {
		cin >> str[i];
		flg[str[i][0] - 'a'] = 1;
		ll s = 1;//权重
		for (ll j = str[i].length() - 1; j >= 0; j--) {//计算字符权重，从后往前依次乘10
			t[str[i][j] - 'a'] += s;
			s *= 10;
		}
	}
	for (ll i = 0; i < 10; i++) {
		a[i].can_be_0 = !flg[i];
		a[i].name = i + 'a';
		a[i].val = t[i];
	}

	sort(a, a + 10, cmp);

	for (ll i = 9; i >= 0; i--) { //特判前导零
		if (a[i].can_be_0) {
			zero_ind = i;
			break;
		}
	}

	ll w = 9; //目前的数
	for (ll i = 0; i < 10; i++) {//计算
		if (i == zero_ind) {
			continue;
		}
		ans += a[i].val * w;
		w--;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

题目传送门：[https://www.luogu.com.cn/problem/CF910C](https://www.luogu.com.cn/problem/CF910C)

这个题目我发现我的代码跑得很快啊，`210ms` 就跑完了，用的则是跟大家与众不同的 `STL`~~（STL大法好）。~~

这道题一看就是贪心，思路也很明确。对于共 $n$ 个字符串，我们每一个字符枚举，看看这个字符占了多少数值。我们从数学考虑，假设当前的字符占这个字符串总右往左第 $x$ 位，那么占的数值就是 $10^{(x-1)}$。

例如：

```
abcd
```

中，`d` 占 $1$，`c` 占 $10$，`b` 占 $100$，`a` 占 $1000$。其实也就是数位分析。

接着我们统计每个字符总共占多少，占的越大那所代表的数字就尽可能小，不过不要忘记首位的情况。

两个 `unordered_map` 就解决了！

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <map>
using namespace std;

unordered_map<char, bool> mp_pd; // 判断当前的字符是否是首位
unordered_map<char, long long> mp; // 储存当前的字符占多少值

bool pd()
{
	unordered_map<char, long long>::iterator ite = mp.end();
	for (auto it = mp.begin(); it != ite; ++it)
	{
		if (it->second != 0)
		{
			return false;
		}
	}
	return true;
}

void print()
{
	printf("print1\n");
	unordered_map<char, long long>::iterator ite = mp.end();
	for (auto it = mp.begin(); it != ite; ++it)
	{
		cout << "key: " << it->first << " value: " << it->second << endl;
 	}
} // 调试使用

void print2()
{
	printf("print2\n");
	unordered_map<char, bool>::iterator ite = mp_pd.end();
	for (auto it = mp_pd.begin(); it != ite; ++it)
	{
		cout << "key: " << it->first << " value: " << it->second << endl;
	}
} // 调试使用

int main()
{
	ios::sync_with_stdio(false);
	bool used_zero = false;
	int now_use = 1;
	long long sums = 0;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		long long len = s.size() - 1, now = 1;
		mp_pd[s[0]] = true;
		for (int i = len; i >= 0; i--)
		{
			mp[s[i]] += now;
			now *= 10;
		}
	}
	/*
	print();
	print2();
	*/
	while (!pd())
	{
		unordered_map<char, long long>::iterator ite = mp.end(), its;
		char xz;
		long long maxn = 0;
		for (auto it = mp.begin(); it != ite; ++it)
		{
			if (it->second > maxn)
			{
				maxn = it->second;
				its = it;
				xz = it->first;
			}
		}
		if (!mp_pd[xz])
		{
			if (!used_zero)
			{
				used_zero = true;
			}
			else
			{
				sums += now_use * maxn;
				now_use++;
			}
		}
		else
		{
			sums += now_use * maxn;
			now_use++;
		}
		its->second = 0;
	}
	cout << sums << endl;
	//system("pause");
	return 0;
}
```

不要抄哦！

---

## 作者：laeva (赞：0)

~~贪心过样例~~

最基本的想法当然是枚举每一个字母可以表示成那一个数字，然后找出其中合法（即没有前导零）且最小的，~~就能解决了~~

#### 这就完了？？

当然是不可能的，~~AC是不会AC的，这辈子都不可能AC的~~

转入正题：

现在让我们观察一组样例：

```python
3
ab
de
aj

```
其中：
$$ab -> a * 10 + b$$
$$de -> d * 10 + e$$
$$aj -> a * 10 + j$$
那么：
$$ab + de + aj->(a * 10 + b) + (d * 10 + e) + (a * 10 + j)$$
$$->a * 20 + d * 10 + b + j$$
现在可以看出要使*ab+de+aj*最小，只需要让*a*最小，*d*次之，然后是*b*，*j*

也就是说，我们把每个字母按它前面的系数从大到小排一遍序，用0~9依次赋值就~~ok~~了

#### 当然，这还不够

有些字母是不可以赋为零的，即样例中的*a*最小值为一，这点当然很好处理，我们只需要在赋值的时候找到最前面的（已排序）可以赋值为0的字母就可以解决


## code
```cpp
//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring> 

#define MAXN 100010
#define mod 1000000007
#define INF 0x7fffffff
#define first fi
#define second se
#define ll long long
#define fom(i, a, b) for (int i = a; i <= b; i++)
#define foi(i, a, b) for (int i = a; i >= b; i--)

int abs(int x) { return x > 0 ? x : -x; }
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }

int read() {
	int ans = 0; char ch = getchar(), t = ch;
	while (ch < '0' || ch > '9') { t = ch; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { ans = ans * 10 + ch - '0'; ch = getchar(); }
	if (t == '-') ans = -ans; return ans;
}

using namespace std;

char s[10];
int o[30];
struct node {
	int w, na; 
}w[30];

bool cmp(node x, node y) { return x.w > y.w; }

int main() {
/*	freopen(".in", "w", stdin);
	freopen(".out", "r", stdout);*/
	int n = read();
	fom(i, 1, n)  {
		scanf("%s", s);
		int l = strlen(s), ans = 1;
		fom(i, 0, l - 1) {
			w[s[l - 1 - i] - 'a'].w += ans;
			w[s[l - 1 - i] - 'a'].na = s[l - 1 - i] - 'a';
			ans *= 10;
			if (i == l - 1) o[s[0] - 'a'] = 1;
		}
	}
	sort(w + 0, w + 10, cmp);
	int pos = 1, vis = 0;
	int ans = 0;
	fom(i, 0, 9) {
		if (!o[w[i].na] && !vis) vis = 1;
		else ans += w[i].w * pos, pos++;
	}
	printf("%d", ans);
	return 0;
}
```

---

