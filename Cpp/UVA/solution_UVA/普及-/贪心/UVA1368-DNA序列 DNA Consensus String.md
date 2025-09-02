# DNA序列 DNA Consensus String

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4114

[PDF](https://uva.onlinejudge.org/external/13/p1368.pdf)

# 题解

## 作者：Jsxts_ (赞：7)

这道题就是一道简单的模拟。

用贪心的思路做，对于字符串的每一位，统计这一位各种字母的个数，找最大的个数（按照字典序），答案累计上即可。

剩下的部分在注释里说明了。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[27];
string s[1010];
int main() {
	int t;
	scanf("%d",&t);//多组数据 
	while (t -- ) {
		int n,m,ans = 0;//ans：最小Hamming值 
		string res = "";//记录答案DNA序列 
		scanf("%d%d\n",&n,&m);
		for (int i = 1;i <= n;i ++ ) {
			cin >> s[i];//每一个DNA序列 
			s[i] = '0' + s[i];
		}
		for (int i = 1;i <= m;i ++ ) {//枚举每一列 
			memset(a,0,sizeof a);//a数组记录每种字母出现的个数 
			int maxx = 0;
			char ch;
			for (int j = 1;j <= n;j ++ ) {
				a[s[j][i]-'A'+1] ++;//同种字母个数加一 
			}
			for (int j = 1;j <= 26;j ++ ) {
				//自动按字典序查找，字典序靠前的优先选中 
				if (maxx < a[j]) {
					maxx = a[j];//找最大值，并记录当前的字母 
					ch = (char)(j+'A'-1);
				}
			}
			res += ch;//DNA序列加上这一轮的字母 
			ans += n - maxx;//累加Hamming值 
		}
		cout << res << endl << ans << endl;
		//DNA序列以及Hamming值 
	}
	return 0;
}
```

这道题我就是当练习模拟的，所以代码写的比较繁琐，但是思路还算清晰。

END

---

## 作者：PC_DOS (赞：6)

本题为一道字符串贪心题，任务是找出与给定的所有DNA串最相近的DNA串并计算其偏差值。

为了寻找与所给DNA串最相似的DNA串，我们可以借助贪心思想，按字符索引检索所有给定的字符串(即按列检索)，找出出现次数最多的碱基并加入答案串(如果有多个最多碱基，则取其中字典序最小者)，并将其他碱基出现的总数加至偏差值上即可。

代码:
```
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
struct Base{ //碱基结构体
	char chrBase; //碱基符号，DNA可取A(腺嘌呤)、C(胞嘧啶)、G(鸟嘌呤)、T(胸腺嘧啶)
	int nCount; //个数
};
bool cmp(Base bseBase1, Base bseBase2){ //排序所用的比较函数
	if (bseBase1.nCount != bseBase2.nCount) //个数不等
		return bseBase1.nCount > bseBase2.nCount; //取个数大者优先
	else //个数相等
		return bseBase1.chrBase < bseBase2.chrBase; //取字典序小者优先
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nTest, nCount, iLength, iError=0; //nTest-测试次数；nCount-DNA串个数；iLength-DNA串长度；iError-偏差值
	Base arrBases[4]; //存放四种密码子的数组
	arrBases[0].chrBase = 'A';
	arrBases[0].nCount = 0;
	arrBases[1].chrBase = 'C';
	arrBases[1].nCount = 0;
	arrBases[2].chrBase = 'G';
	arrBases[2].nCount = 0;
	arrBases[3].chrBase = 'T';
	arrBases[3].nCount = 0; //数组初始化
	register int i, j, k; //循环计数器
	string sDNA, sAns(""); //sDNA-暂存输入的DNA串；sAns-答案串
	vector<string> arrDNA; //存放输入的DNA的动态数组
	cin >> nTest; //读入测试次数
	for (i = 1; i <= nTest; ++i){ //逐个读入
		cin >> nCount >> iLength; //读入DNA串个数和长度
		for (j = 1; j <= nCount; ++j){ //读入DNA串
			cin >> sDNA; //读入暂存区
			arrDNA.push_back(sDNA); //压入动态数组
		}
		for (j = 0; j < iLength; ++j){ //按字符索引检索所有给定的字符串(即按列检索)
			for (k = 0; k < nCount; ++k){ //遍历动态数组
				switch (arrDNA[k][j]){ //判断碱基
				case 'A': //腺嘌呤
					++arrBases[0].nCount;
					break;
				case 'C': //胞嘧啶
					++arrBases[1].nCount;
					break;
				case 'G': //鸟嘌呤
					++arrBases[2].nCount;
					break;
				case 'T': //胸腺嘧啶
					++arrBases[3].nCount;
					break;
				}
			}
			sort(arrBases, arrBases + 4, cmp); //快排
			sAns += arrBases[0].chrBase; //将出现次数最多的碱基(即数组第一项)并加入答案串(如果有多个最多，则取其中字典序最小者)
			iError += arrBases[1].nCount + arrBases[2].nCount + arrBases[3].nCount; //将其他碱基出现的总数加至偏差值上
			arrBases[0].chrBase = 'A';
			arrBases[0].nCount = 0;
			arrBases[1].chrBase = 'C';
			arrBases[1].nCount = 0;
			arrBases[2].chrBase = 'G';
			arrBases[2].nCount = 0;
			arrBases[3].chrBase = 'T';
			arrBases[3].nCount = 0; //碱基数组初始化
		}
		cout << sAns << '\n' << iError << '\n'; //输出答案串和偏差值，勿忘换行
		sAns = ""; //清空答案串
		iError = 0; //偏差值归零
		arrDNA.clear(); //清空存放DNA串的数组
	}
	return 0; //结束
}
```


---

## 作者：lxgw (赞：4)

## 题目思路
这题用字符串模拟就好了，每次要找出出现次数最多的字母（按字典排序，话说我曾经死在这），然后依次输出就好了

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
string a[1005];//约等于定义一个char类型的a[1005][255]
int t[100]/*用来存每个DNA出现的次数*/,ti,n,m,i,j,mx,sum;
int s[]={'A','C','G','T'};//四种可能出现的DNA
int main()
{
    char harm;//表示每次被选出的字母
    cin>>ti;
    while(ti--)//ti组数据
    {
        cin>>n>>m;
        for(i=0;i<n;i++)
            cin>>a[i];//输入字符串
        string ans;//用来存储答案
        sum=0;//把harmming距离归零
        for(i=0;i<m;i++)
        {
            mx=0;//归零
            for(j=0;j<4;j++) t[s[j]]=0;//把t数组归零
            for(j=0;j<n;j++) t[a[j][i]]++;//把出现过的DNA的次数加一
            for(j=0;j<4;j++) mx=max(mx,t[s[j]]);//mx表示最多的出现次数
            for(j=0;j<4;j++)
                if(t[s[j]]==mx)
                {
                    harm=s[j];
                    break;//第一次找到字母就直接break掉
                }
            ans+=harm;//ans加上当前选出的字符
            for(j=0;j<4;j++)
                if(s[j]!=harm)
                    sum+=t[s[j]]; //与harm不一样的话harmming距离就加一 
        }
        cout<<ans<<endl<<sum<<endl;//输出答案，要注意格式
    }
    return 0;//完结撒花
}
```


------------
谢谢qwq


---

## 作者：梦里调音 (赞：4)

什么生物之类的我是不懂，~~所以数组开的大了一匹~~

还有，本人思路~~麻烦~~**通俗易懂**，做好心理准备~~和欣赏**又臭又长**的代码的准备~~

我用了三重循环：

①要求先输入一个数，直接在循环里输入；

②长度为字符串长度，挨个判断；

③长度为字符串个数，计算每个字符的出现次数，并进行判断，选取出现最多的字符输出（如有相等则按照字典顺序）

最后提醒：注意输出格式

好了，敬请欣赏代码~

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int i,j,k,r,n,m,l;
	string s[51];
	cin>>n;
	for(i=1;i<=n;i++){	
		int cuo=0;
		cin>>m>>l;
		for(j=1;j<=m;j++)cin>>s[j];
		for(k=0;k<l;k++){
			int c[1001]={0},ans=0,fal=0;
			char p;
			for(r=1;r<=m;r++)c[s[r][k]]++;
			for(r=1;r<=m;r++){
				if(c[s[r][k]]>ans||(c[s[r][k]]==ans&&s[r][k]<p)){
					ans=c[s[r][k]];
					fal=m-ans;
					p=s[r][k];
				}
			}
			cuo+=fal;
			cout<<p;
		}
		cout<<endl<<cuo<<endl;
	}
    return 0;
} 
```

---

## 作者：2020Juruo (赞：2)

思路简洁明了，纵向对比，输出最多的一个字母。代码如下。
```
#include<math.h>
#include<stdio.h>
#include<string.h>
#define maxn 1005
char str[55][maxn];
char mark[10]={0,'A','T','G','C'};
int main()
{
	int m,n;
	while(scanf("%d",&m)==1&&m)
	{
		scanf("%d",&n);
		getchar();//吸收回车
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
				str[i][j]=getchar();
			getchar();//吸收回车
		}
		int sum[maxn]={0};
		for(int i=1;i<=n;i++)
		{
			memset(sum,0,sizeof(sum));//注意这里有清空数组！！！
			for(int j=1;j<=m;j++)//统计每个出现的次数
			{
				if(str[j][i]=='A')sum[1]++;
				else if(str[j][i]=='T')sum[2]++;
				else if(str[j][i]=='G')sum[3]++;
				else if(str[j][i]=='C')sum[4]++;
			}
			int k,max=1;
			for(k=1;k<=4;k++)
				if(sum[max]<sum[k])max=k;//找出出现次数最多的一个字母的编号并赋值给max
			printf("%c",mark[max]);
		}
		getchar();
	}
	return 0;
}

---

## 作者：Night12138 (赞：2)

这里给一个现代C++的比较好的解法，可读性或许比较强，而且在处理最大值上可能会很简单。
核心思路和另外两位dalao大致相同。
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int n;
	const string DNAName = "ACGT"; // 声明一个常量字符串，用于读取最大的字符
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num, size;
		cin >> num >> size;
		vector<string> s;          // 用于存储字符串的vector容器，这样不用开数组或者自己动态申请
		string tmp;

		for (int j = 0; j < num; j++) {
			cin >> tmp;
			s.push_back(tmp);      // vector的push_back方法，压入vector的结尾
		}

		int hammingDistance = 0;   // 初始化结果 即Hamming距离

		for (int j = 0; j < size; j++) {
			vector<int> DNAs = { 0,0,0,0 };   // 初始化一个类型为int的vector，其中每一个元素代表着DNA中的A C G T，按字典顺序排列
			for (int k = 0; k < num; k++) {
				switch (s[k][j])              // 用switch判断这个字符是什么
				{
				case 'A': DNAs[0]++; break;   // 出现次数+1
				case 'C': DNAs[1]++; break;
				case 'G': DNAs[2]++; break;
				case 'T': DNAs[3]++; break;
				}
			}
			int max = distance(DNAs.begin(), max_element(DNAs.begin(), DNAs.end()));  // STL-algorithm的方法，首先max_element是读出vector中最大的元素的迭代器
			                                         // 若两个相同则选择先出现的一个，即vector初始化按字典排序的好处
			                                         // distance是计算两个迭代器的距离，max_element返回一个最大值的迭代器，和初始位置迭代器一起就能算出下标
			cout << DNAName[max];                    // 读出开始声明的常量字符串对应的字母，输出
			for (int k = 0; k < 4; k++)if (k != max)hammingDistance += DNAs[k];       // 把剩下的元素加在Hamming距离里
		}
		cout << endl << hammingDistance << endl;
	}
	return 0;
}
```

---

## 作者：fjy666 (赞：0)

### 0x01 思路
这是一道字符串贪心题。  
对于每一个位置 $i$ $(1 \le i \le n)$，我们考虑每一个串相同的位置 $i$ 的字符，统计出现最多的字符，再加到答案字符串里去。
- 字符出现顺序相同，一定要判断字典序！

为什么能这样做呢？  
首先，可以知道答案字符串 `ans_str` 中的**任意一个**位置 $i$ 和位置 $j$，它们都**相互没有影响**。  
什么意思呢？  
就是 $ans\_str_j$ 无论是什么字符，都和 $ans\_str_i$ 的 $\texttt{Hamming}$ 距离贡献值无关。
> 贡献值，就是一个字符对整个 $\texttt{Hamming}$ 距离之和累加了多少

反之同理。  
本题中，是想要 $\texttt{Hamming}$ 距离越少越好，所以就要让每个字符的贡献值越少越好。  
显然，我们选取每一位中出现最多的字符 $X$ ，可以让这一位的贡献值最小。设它的出现次数 $C$ ，那它的贡献值就是 $m - C$ 。  
注意：枚举每一位的时候按顺序！  
然后我们就把它拼接到 $ans\_str$ 中就 $\mathrm{AC}$ 了此题。

------------
### 0x02 代码
```cpp
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
struct Counter
{
	int cnt_;
	char chr_;
	void Init(char chr__)
	{
		chr_ = chr__;
		cnt_ = 0;
	}
	Counter()
	{
		Init('A');
	}
	bool operator < (const Counter& x)const
	{
		rtn this->cnt_ > x.cnt_ || (this->cnt_ == x.cnt_ && this->chr_ < x.chr_);
	}
}; 
Counter cnt[5];
char str[51][10011]; 
int main()
{
	int TestCases;
	scanf("%d",&TestCases);
	while(TestCases--)
	{
		int m,n,maxn = 0;
		scanf("%d%d",&m,&n);
		fo(i,1,m)
			scanf("%s",str[i]+1);
		char ans_str[100011],*Str = ans_str;
		fo(i,1,n)
		{
			cnt[1].Init('A');
			cnt[2].Init('C');
			cnt[3].Init('G');
			cnt[4].Init('T');
			fo(j,1,m)
				switch(str[j][i])
				{
					case 'A':
						cnt[1].cnt_ ++;
						break;
					case 'C':
						cnt[2].cnt_ ++;
						break;
					case 'G':
						cnt[3].cnt_ ++;
						break;
					case 'T':
						cnt[4].cnt_ ++;
						break;
				}
			std::sort(cnt+1,cnt+1+4);
			*Str++ = cnt[1].chr_;
			maxn += m - cnt[1].cnt_; 
		}
		*Str = '\0';
		printf("%s\n%d\n",ans_str,maxn);
	}
    rtn 0;
}
```

---

