# Kruscal的加法

## 题目背景

奶牛 Kruscal 认为人类的加法太落后了。比如说有时候想要用加法计算 `+15*3`，只能写成 `+15+15+15`，真是浪费精力啊！于是，Kruscal 决定开发出一种新的加法算式。

## 题目描述

当然，新的算式也是建立在原本算式的基础上的，不同就在于上式可以直接写成 `+++15`，同理，对于 `-15*3` 这样的算式可以写成 `---15`。一段时间后，Kruscal 又被那无穷多个 `+-` 号囧到了，于是他又将这个算式改进了一下。

比如 `+15*3` 又可以写成 `+(3)15`，同样，`-15*3` 等价于 `-(3)15`。但从上面可以看出，对于乘数较小的情况，如 `+++15` 这样的表述还是很方便的，于是在新的算式中还是保留了这种形式。

对于算式还要做一点特殊的说明：`+15*3` 转换成 Kruscal 型算式时可以写成 `+++15` 或 `+(3)15`，但不可以写成 `++(2)15` 这样的形式。

对于算式 `23+15*3-2` 可以表示为以下几种形式：`23+++15-2`、`23+(3)15-2`、`+23+++15-2`、`+23+(3)15-2、+(1)23+(3)15-(1)2`。不会出现如下几种形式：`(1)23+++15-2`、`+23++(2)15-(1)2`、`23+++15-2+(0)100`、`23-(-3)15-2`。

## 说明/提示

对于 $100 \%$ 的数据，算式长度不超过 $2000$。

## 样例 #1

### 输入

```
+(1)23+(3)15-(1)2```

### 输出

```
66```

# 题解

## 作者：吹雪吹雪吹 (赞：14)

## ~~最小生成树~~Kruscal的加法


本蒟蒻写得很粗鲁，请dalao见谅。

AC须准备：

可以不考虑负数的高精度（加法，乘法，减法），我喜欢叫它Int

Int ans1,ans_1; ans1记录+x，ans_1记录-x

接下来：

把数字按照不同表示方法拿下来，累加到ans1或ans_1

比较ans1与ans_1的大小，处理后输出。

具体请参考代码：
```cpp
//我喜欢把某一部分的注释写在那一部分下面
#include<cstdio>
#include<cstring>
#include<algorithm>
#define TT 10000

using namespace std;

char s[2005];

class Int
{
public:
	int a[505],len;
	Int()
	{
		memset(a,0,sizeof(a));
		len=0;
	}
	Int(int x)
	{
		memset(a,0,sizeof(a));
		len=0;
		while(x)
		{
			a[++len]=x%TT;
			x/=TT;
		}
	}
	Int operator +(Int b)
	{
		Int c;
		c.len=max(len,b.len);
		for(int i=1;i<=c.len;++i)
		{
			c.a[i]+=a[i]+b.a[i];
			c.a[i+1]=c.a[i]/TT;
			c.a[i]%=TT;
		}
		if(c.a[c.len+1])
			c.len++;
		return c;
	}
    //高精度加法不解释
	Int operator *(Int b)
	{
		Int c;
		c.len=len+b.len;
		for(int i=1;i<=len;++i)
		{
			for(int j=1;j<=b.len;++j)
			{
				c.a[i+j-1]+=a[i]*b.a[j];
				c.a[i+j]+=c.a[i+j-1]/TT;
				c.a[i+j-1]%=TT;
			}
		}
		while(!c.a[c.len])
			c.len--;
		return c;
	}
    //高精度乘法不解释
	Int operator -(const Int b)
	{
		Int c;
		c.len=max(len,b.len);
		for (int i=1;i<=c.len;i++)
		{
			c.a[i]+=a[i]-b.a[i]+TT;
			c.a[i+1]+=c.a[i]/TT-1;
			c.a[i]%=TT;
		}
		while (c.len>1&&!c.a[c.len]) c.len--;
		return c;
	}
    //高精度减法不解释
	bool operator <(Int b)const
	{
		if(b.len>len)
			return true;
		else if(len>b.len)
			return false;
		for(int i=len;i>0;--i)
		{
			if(b.a[i]>a[i])
				return true;
			if(b.a[i]<a[i])
				return false;
		}
		return false;
	}
    //小于不解释
	void write()
	{
		printf("%d",a[len]);
		for(int i=len-1;i>=1;--i)
			printf("%04d",a[i]);
		printf("\n");
	}
    //输出
}ans1,ans_1;
//ans1记录+x，ans_1记录-x

void ToInt64(int &i)
{
	Int ret=0,cs=0,p=10;
	int f=1;
	if(s[i]=='-')
		f=-1;
	if(s[i+1]=='(')
	{
    //如果按+(2)33表达
		i+=2;
		while(s[i]>='0'&&s[i]<='9')
		{
			Int res=(int)s[i]-'0';
			cs=cs*p+res,++i;
		}
        //拿下括号内数字
		i++;
		while(s[i]>='0'&&s[i]<='9')
		{
			Int res=(int)s[i]-'0';
			ret=ret*p+res,++i;
		}
        //取走要加上的数字
		Int c=ret*cs;
        //这次运算的结果
		if(f==-1)
			ans_1=ans_1+c;
		else
			ans1=ans1+c;
	}
	else if(s[i+1]>='0'&&s[i+1]<='9')
	{
    //如果直接按照+233表达
    //这段里面有个防抄袭用的"错误"
		i++;
		while(s[i]>='0'&&s[i]<='9')
		{
			Int res=(int)s[i]-'0';
			ret=ret*p+res,++i;
		}
        //取走数字
		int c=ret;
		if(f==-1)
			ans_1=ans_1+c;
		else
			ans1=ans1+c;
	}
	else
	{
    //如果是+++233的形式
		i++,cs=1;
		Int res=1;
		while(s[i]=='-'||s[i]=='+')
		{
			cs=cs+res,++i;
		}
        //数一下符号个数
		while(s[i]>='0'&&s[i]<='9')
		{
			Int res=(int)s[i]-'0';
			ret=ret*p+res,++i;
		}
        //拿走数字
		Int c=ret*cs;
		if(f==-1)
			ans_1=ans_1+c;
		else
			ans1=ans1+c;
	}
    //话说+233与+++233是可以并到一起的，这里是我写的过于粗鲁了
}

int main()
{
//不要在luogu配文件！自行遮蔽
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
//不要在luogu配文件！自行遮蔽

	scanf("%s",s+1);
	int i=1;
	while(s[i])
		ToInt64(i);
	if(!(ans1<ans_1)&&!(ans_1<ans1))
	{
		printf("0");
	}
    //如果Σx>0=Σx<0，输出0
	else if(ans1<ans_1)
	{
		ans_1=ans_1-ans1;
		printf("-");
		ans_1.write();
	}
    //如果减数大于被减数，输出一个负号以及ans_1-ans1
	else
	{
		ans1=ans1-ans_1;
		ans1.write();
	}
    //被减数大于减数，直接输出ans1-ans_1
	return 0;
}
```

---

## 作者：赤霄 (赞：13)

这可能是最长的一片题解，但思路应该是很清晰的
首先这道题可以模拟或者重载
因为重载看着太丑了，我选择了模拟大法
首先思路如下
考虑这串字符可能有几种形式
1. +++++数字  
2. +（数字）数字
3. +数字
4. 只有数字
5. ----数字
6. -（数字）数字
7. -数字

因为要考虑正负号所以不能直接加或减
正加正直接加；正加负变成正减正；负加负，改为正加正，标记不变；负减负变成正减负；
但如果每次操作都考虑正负号会非常的繁琐
所以我们用两个数组 一个记录加的操作的总和 一个记录减的操作的总和 这样只需要在输出答案的时候判断一下正负号即可
另外还有读入时数是从高位开始存的
所以每次读入后我们都翻转一下数组 让最低位在数组开始的位置
这样进位的操作会很好实现
还要处理好两个答案数组的长度

接下来就放出我的巨长的代码
————————>
```cpp

# include <iostream>
# include <string>
# include <cstring>
# include <algorithm>
# include <cstdio>
# define ll long long
using namespace std;

char s[1000100];
int len,tot,ans_l = 1,cnt,ans_r = 1,ans_len;
int st[1000100],a[1000100],ans1[1000100],que[1000000],mu[1000100],ans2[1000100],ans[1000100];

void change(){
	for (int i = 1 ; i <= tot; i ++) a[i] = st[i];
	for (int  i = 1 ; i <= tot ; i++) st[i] = a[tot-i+1];
}

void tchange(){
	for (int i = 1 ; i <= cnt ; i++) a[i] = que[i];
	for (int i= 1 ; i <= cnt ; i++) que[i] = a[cnt-i+1];
}

void mul(int sum){
	int jin = 0;
	for (int i = 1 ; i <= tot ;i++){
		st[i] = st[i] * sum + jin;
		jin = st[i] / 10;
		st[i] %= 10;
	}
	if(jin){tot++; st[tot] += jin;}
}

void add(){
	int r = max(ans_l,tot); int jin = 0;
	for (int i = 1 ; i <= r ; i++){
		ans1[i] = ans1[i] + st[i] + jin;
		jin = ans1[i] / 10;
		ans1[i] %= 10;
	}
	ans_l = r;
	while(ans1[ans_l] == 0) ans_l--;
}

void Add(){
	int r = max(ans_r,tot); int jin = 0;
	for (int i = 1 ; i <= r ; i++){
		ans2[i] = ans2[i] + st[i] + jin;
		jin = ans2[i] / 10;
		ans2[i] %= 10;
	}
	ans_r = r;
	while(ans2[ans_r] == 0) ans_r--;
}

void Mmul(){
	memset(mu,0,sizeof(mu));
	int jin = 0; int lenn = 1;
	for (int i = 1 ; i <= tot ; i++){
		for (int j = 1 ; j <= cnt ; j++){
			mu[i+j-1] += st[i] * que[j];
			mu[i+j] += mu[i+j-1] / 10;
			mu[i+j-1] %= 10;
		}
	}
	lenn = tot+cnt;
	while(mu[lenn] == 0) lenn--; 	
	memset(st,0,sizeof(st));
	for (int i = 1 ; i <= lenn ; i++) st[i] = mu[i];
	tot = lenn;
}

void jian1(){
	int r = max(ans_l,ans_r); int jin = 0;	
	for (int i = 1 ; i <= r ; i++){
		ans[i] = ans2[i] - ans1[i];
		if(ans[i] < 0) ans[i] += 10,ans2[i+1] -= 1;
	}	
	while(ans[r] == 0) r--;
	ans_len = r;
}

void jian2(){
	int r = max(ans_l,ans_r); int jin = 0;
	for (int i = 1 ; i <= r ; i++){
		ans[i] = ans1[i] - ans2[i];
		if(ans[i] < 0) ans[i] += 10, ans1[i+1] -= 1;
	}
	while(ans[r] == 0) r--;
	ans_len = r;
}

bool check(){
	if(ans_l < ans_r) return 1;
	if(ans_l > ans_r) return 0;
	if(ans_l == ans_r){
		for (int i = ans_l ; i >= 1 ; i--){
			if(ans1[i] < ans2[i]) return 1;
			if(ans1[i] > ans2[i]) return 0;
			if(ans1[i] == ans2[i]) continue;
		}
	}
	return 0;
}

int main(){
	cin >> s+1;
	len = strlen(s+1) ;
	for (int i = 1 ; i <= len ; i++){
		if(s[i] == '+' && s[i+1] == '+'){
			memset(st,0,sizeof(st));
			int x = i; cnt = 0; tot = 0;
			while(s[x] <'0' || s[x] >'9') x++,cnt++;
			while(s[x] >= '0' && s[x] <= '9') st[++tot] = s[x++] - '0';
			change(); mul(cnt); add();
			i = x - 1; continue;
		}
		if(s[i] == '+' && s[i+1] == '('){
			memset(st,0,sizeof(st)); memset(que,0,sizeof(que));
			int x = i + 2; tot = 0; cnt = 0;
			while(s[x] >='0' && s[x] <='9') que[++cnt] = s[x++] - '0'; 
			tchange();
			if(s[x] == ')'){
				x ++;
				while(s[x] >='0' && s[x] <='9') st[++tot] = s[x++] - '0';
				 change();	
			}			
			Mmul(); add();
			i = x - 1; 
			continue;		}
		if(s[i] == '+'){
			if(s[i+1] >= '0' && s[i+1] <= '9'){
				memset(st,0,sizeof(st));
				int x = i + 1; tot = 0;
				while(s[x] >= '0' && s[x] <= '9') st[++tot] = s[x++] - '0';
				change(); add();
				i = x - 1; continue;
			}	
		}
		if(s[i] >= '0' && s[i] <= '9'){
			memset(st,0,sizeof(st));
			int x= i; tot = 0;
			while(s[x] >= '0' && s[x] <= '9' ) st[++tot] = s[x++] - '0';
			change(); add();
			i = x - 1;
			continue; 
		}
		if(s[i] == '-' && s[i+1] == '-'){
			memset(st,0,sizeof(st));
			int x = i; cnt = 0; tot = 0;
			while(s[x] <'0' || s[x] >'9') x++,cnt++;
			while(s[x] >= '0' && s[x] <= '9') st[++tot] = s[x++] - '0';
			change(); mul(cnt); Add();
			i = x - 1;
			continue;
		}
		if(s[i] == '-' && s[i+1] == '('){
			memset(st,0,sizeof(st)); memset(que,0,sizeof(que));
			int x = i + 2; tot = 0; cnt = 0;
			while(s[x] >='0' && s[x] <='9') que[++cnt] = s[x++] - '0'; tchange();
			if(s[x] == ')'){
				x ++;
				while(s[x] >='0' && s[x] <='9') st[++tot] = s[x++] - '0';
			 	change();
			}
			Mmul(); Add();
			i = x - 1; continue;
		}
		if(s[i] == '-'){
			if(s[i+1] >= '0' && s[i+1] <= '9'){
				memset(st,0,sizeof(st));
				int x = i + 1; tot = 0;
				while(s[x] >= '0' && s[x] <= '9') st[++tot] = s[x++] - '0';
				change(); Add();
				i = x - 1; continue;
			}
		}	
	}
	if(check()){ cout<<"-"; jian1();}
	else jian2();

	for (int i = ans_len ; i >= 1 ; i --) cout<<ans[i]; 
	if(ans_len <= 0) cout<<0<<endl;
	return 0;
}
/*
+(255)10---3-(23)100
*/
```


---

## 作者：HanPi (赞：8)

首先读题,通过题目我们可以得知:
- 算式只存在 '+' , '-' , '*' 的运算且不用考虑运算优先级
- 不会出现连乘

发现不用考虑优先级后我的第一想法是 
##### 将算式拆分成一些小的单一算式( 运算符 + 数字 )再计算
如: 处理 str="+++1++2+(3)3" :

1. 找到在上一个运算符号后重新出现的第一个运算符号位置 i=0
2. 从找到的运算符位置起找到 前一位不是+或-的 运算符的位置 j=4
3. str[i]~str[j] (不含str[j]) 即为一组单一算式,计算其结果并叠加到ans上
4. 重复以上操作

## 拆分代码:
```c
	// 因为要靠运算符进行标识,所以需要在前后端添加符号

	scanf("%s", &(str[1]));// 直接从第一位开始输入
	if (str[1] != '+' && str[1] != '-')str[0] = '+';// 避免重复
	else str[0] = ' ';
	int len = strlen(str);
	str[len] = '+';
	//str[len+1]='\0';// 在全局定义的数组默认初始化为0
    
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '+' || str[i] == '-') // 找到运算符
		{
			for (int j = i + 1; j < len; j++) // 开始找结束位置
			{
				if (str[j] == '+' || str[j] == '-')
				{
					if (str[j - 1] != '+' && str[j - 1] != '-')
					{
						for (int k = i; k < j; k++)stmp[k - i] = str[k];// 拷贝这一段字符串
						stmp[j - i] = 0;

						// TODO : 处理这一段算式
                        
						i = j - 1; // 跳到下一段
						break;
					}
				}
			}
		}
	}
```

### 然后处理这一小段代码:
```c
int GetVal(const char* str)
{
	int num = 0, plus = 0, minus = 0;
   // num存括号外的数,plus和minus分别存储加(减)次数
	int len = strlen(str);
	int tmp = 0, tmpn = 0;
   // tmp标记是在记录括号内的数还是要计算的数
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '+')plus++;
		else if (str[i] == '-')minus++;
		else if ('0' <= str[i] && str[i] <= '9')
		{
        // 计算数字
			if (tmp)
			{
				tmpn = tmpn * 10 + str[i] - '0';
			}
			else
			{
				num = num * 10 + str[i] - '0';
			}
		}
		else if (str[i] == '(')// 标记
		{
			tmp = 1;
		}
		else if (str[i] == ')')
		{
			tmp = 0;
		}
	}

	if (tmpn)tmpn--;// 如果有括号中的数,则减去括号前的符号所代表的一次

	if (plus)
	{
		plus += tmpn;// 叠加
		return num * plus;
	}
	else
	{
		minus += tmpn;// 叠加
		return -num * minus;
	}
}
```

~~(然后愉快的40分了)~~

这个时候瞄到题目下方说的 "算式长度不超过2000" 就很明显要使用高精度

~~(我看Dalao们都是自己写了一个类,不过我比较弱,只能写个结构体来代替)
高精度几乎全忘光的我写了将近一天...~~

```c
typedef struct _StrNumber
{
	char num[8848];
	int flag; // 是否有负号
}LLL;

void pluss(char* numA, char* numB); // 加法 将结果存入numA
void minuss(char* numA, char* numB, char* ans); // 减法,将结果存入ans
void cf(char* numA, char* numB); // 乘法(忘了英文怎么拼),将结果存入numA
void LLLcmp(char* a,char* b); // 比较,返回值类似strcmp

// 实现:

/*高精度加法 将结果存入numA*/
void pluss(char* numA, char* numB)
{
	int arr1[2008] = { 0 }, arr2[2008] = { 0 }, len, len1, len2, i, j;

	len1 = strlen(numA);
	for (i = 0; i < len1; i++)//字符串倒叙导入数组，方便从低位开始运算
		arr1[i] = numA[len1 - 1 - i] - '0';

	len2 = strlen(numB);
	for (i = 0; i < len2; i++)
		arr2[i] = numB[len2 - 1 - i] - '0';//字符串中的是字符，要转换成数字
	len = (len1 > len2) ? len1 : len2;
	for (i = 0; i < len; i++)
	{
		arr1[i + 1] += j = (arr1[i] + arr2[i]) / 10;//进位
		arr1[i] = (arr1[i] + arr2[i]) % 10;//保留
	}
	if (j)len++;//最后一位是否进位
	for (i = 0; i < len; i++)
		numA[i] = arr1[len - 1 - i] + '0';
		//printf("%d", arr1[len - 1 - i]);
}

/*减法*/
char tmp[2008] = { 0 };
int arr1[2008] = { 0 }, arr2[2008] = { 0 };
void minuss(char* numA, char* numB, char* ans)
{
	memset(tmp, 0, 2008);
	memset(arr1, 0, 2008*4);
	memset(arr2, 0, 2008*4);
	int len = 0, len1 = strlen(numA), len2 = strlen(numB);
	int i, j;
	int flag = 0;

	len1 = strlen(numA), len2 = strlen(numB);
	for (i = 0; i <= len1 - 1; i++)arr1[len1 - i] = numA[i] - '0';
	for (i = 0; i <= len2 - 1; i++)arr2[len2 - i] = numB[i] - '0';
	i = 1;
	while (i <= len1 || i <= len2)
	{
		if (arr1[i] < arr2[i])
		{
			arr1[i] += 10;
			arr1[i + 1]--;
		}
		tmp[i] = arr1[i] - arr2[i] + '0';
		i++;
	}
	len = i;
	while ((tmp[len - 1] == '0') && (len >= 0))len--;
	j = 0;
	for (i = len - 1; i >= 0; i--)
	{
		ans[j] = tmp[i];
		//printf("'%c\n", tmp[i]);
		j++;
	}
}

int a[2008] = { 0 }, b[2008] = { 0 }, c[4016] = { 0 };
void cf(char* numA, char* numB)
{
	int lena, lenb, lenc, i, j, x;

	memset(c, 0, 4016 * sizeof(int));

	lena = strlen(numA); lenb = strlen(numB);
	for (i = 0; i < lena; i++) a[lena - i-1] = numA[i] - '0';
	for (i = 0; i < lenb; i++) b[lenb - i-1] = numB[i] - '0';

	for (i = 0; i < lena; i++)
	{
		x = 0;
		for (j = 0; j < lenb; j++)/*对乘数的每一位进行处理*/
		{
			c[i + j] = a[i] * b[j] + x + c[i + j];/*当前乘积+上次乘积进位+原数*/
			x = c[i + j] / 10;
			c[i + j] %= 10;
		}
		c[i + lenb] = x;
	}

	lenc = lena + lenb;
	while (c[lenc - 1] == 0 && lenc > 1)/*删除前导0*/
		lenc--;
	j = 0;
	for (i = lenc - 1; i >= 0; i--)
	{
		//printf("%d_", c[i]);
		numA[j] = c[i] + '0', j++;
	}
}

int LLLcmp(char* a, char* b)
{
	// -1:a小,0:相等,1:b小
	int len1 = strlen(a), len2 = strlen(b);
	if (len1 < len2)return -1;
	else if (len1 > len2)return 1;

	for (int i = 0; i < len1; i++)
	{
		if (a[i] < b[i])return -1;
		else if (a[i] > b[i])return 1;
	}
	return 0;
}

```
为了适配高精度,代码也要改动亿下
```c
// 求出str算式的值
void GetVal(const char* str)
{
	char plus[2008] = {0}, minus[2008] = { 0 };

	/*plus 和 minus 分别表示加(减)几次*/
	long long len = strlen(str);
	/*
	* flag 标识当前计算的是括号内的数字还是括号外的
	* num 储存括号外的数 tmpn 储存括号内的数
	*/
	long long flag = 0;
	char num[2008] = { 0 }, tmpn[2008] = { 0 };

	for (int i = 0; i < len; i++)
	{
		if (str[i] == '+')
		{
			pluss(plus, "1");
		}
		else if (str[i] == '-')
		{
			pluss(minus, "1");
		}
		else if (str[i] == '(')
		{
			flag = 1;
		}
		else if (str[i] == ')')
		{
			flag = 0;
		}
		else if ('0' <= str[i] && str[i] <= '9')
		{
			/*计算数字*/
			if (flag)
			{
				//tmpn = tmpn * 10 + str[i] - '0';
				int e = strchr(str, ')') - str;
				// 找到右括号的位置,直接复制
				for (int j = i; j < e; j++)
				{
					tmpn[j - i] = str[j];
				}
				flag = 0;
				i = e;
			}
			else
			{
				//num = num * 10 + str[i] - '0';
				for (int j = i; j < len; j++)
				{
					num[j - i] = str[j];
				}
				break;
			}
		}
	}

	if (tmpn[0])minuss(tmpn, "1", tmpn);
	
	if (plus[0])/*如果是加*/
	{	
		pluss(plus, tmpn);
		
		cf(num, plus);
		if (ans.flag == 0)
		{
			// 如果原数是正数,就直接加
			pluss(ans.num, num);
		}
		else
		{
			// 否则是负数
			int tmp = LLLcmp(ans.num, num);
			if (tmp == 0)
			{
				// 如果相同相加就是0
				ans.flag = 0;
				ans.num[0] = '0';
				ans.num[1] = '\0';
			}
			else if (tmp > 0)
			{
				// 如果num较小则还是负数,数值变为ans-num
				ans.flag = 1;
				minuss(ans.num, num, ans.num);
			}
			else if (tmp < 0)
			{
				// 如果原数较小则变为正数,数值变为num-ans
				ans.flag = 0;
				minuss(num, ans.num, ans.num);

			}
		}
	}
	else/*否则是减*/
	{
		pluss(minus, tmpn);

		cf(num, minus);

		if (ans.flag == 1)
		{
        // 如果是负数,则直接增加数值
			pluss(ans.num, num);
		}
		else
		{
			int tmp = LLLcmp(ans.num, num);
			if (tmp == 0)
			{
				ans.flag = 0;
				ans.num[0] = '0';
				ans.num[1] = '\0';
			}
			else if (tmp > 0)
			{
            // 减数小于被减数,仍是正数
				ans.flag = 0;
				minuss(ans.num, num, ans.num);
			}
			else if (tmp < 0)
			{
            // 被减数小于减数,变为负数
				ans.flag = 1;
				minuss(num, ans.num, ans.num);
			}
		}
	}
}
```

# 完整代码
~~(长暴了)~~
```c
// P1557 Kruscal的加法
//#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>

char str[2008], stmp[2008];
#define MAX 8848

typedef struct _StrNumber
{
	char num[MAX];
	int flag; // 是否有负号
}LLL;

LLL ans;

/*高精度加法 将结果存入numA*/
void pluss(char* numA, char* numB)
{
	int arr1[2008] = { 0 }, arr2[2008] = { 0 }, len, len1, len2, i, j;

	len1 = strlen(numA);
	for (i = 0; i < len1; i++)//字符串倒叙导入数组，方便从低位开始运算
		arr1[i] = numA[len1 - 1 - i] - '0';

	len2 = strlen(numB);
	for (i = 0; i < len2; i++)
		arr2[i] = numB[len2 - 1 - i] - '0';//字符串中的是字符，要转换成数字
	len = (len1 > len2) ? len1 : len2;
	for (i = 0; i < len; i++)
	{
		arr1[i + 1] += j = (arr1[i] + arr2[i]) / 10;//进位
		arr1[i] = (arr1[i] + arr2[i]) % 10;//保留
	}
	if (j)len++;//最后一位是否进位
	for (i = 0; i < len; i++)
		numA[i] = arr1[len - 1 - i] + '0';
		//printf("%d", arr1[len - 1 - i]);
}

/*减法*/
char tmp[2008] = { 0 };
int arr1[2008] = { 0 }, arr2[2008] = { 0 };
void minuss(char* numA, char* numB, char* ans)
{
	memset(tmp, 0, 2008);
	memset(arr1, 0, 2008*4);
	memset(arr2, 0, 2008*4);
	int len = 0, len1 = strlen(numA), len2 = strlen(numB);
	int i, j;
	int flag = 0;

	len1 = strlen(numA), len2 = strlen(numB);
	for (i = 0; i <= len1 - 1; i++)arr1[len1 - i] = numA[i] - '0';
	for (i = 0; i <= len2 - 1; i++)arr2[len2 - i] = numB[i] - '0';
	i = 1;
	while (i <= len1 || i <= len2)
	{
		if (arr1[i] < arr2[i])
		{
			arr1[i] += 10;
			arr1[i + 1]--;
		}
		tmp[i] = arr1[i] - arr2[i] + '0';
		i++;
	}
	len = i;
	while ((tmp[len - 1] == '0') && (len >= 0))len--;
	j = 0;
	for (i = len - 1; i >= 0; i--)
	{
		ans[j] = tmp[i];
		//printf("'%c\n", tmp[i]);
		j++;
	}
}

int a[2008] = { 0 }, b[2008] = { 0 }, c[4016] = { 0 };
void cf(char* numA, char* numB)
{
	int lena, lenb, lenc, i, j, x;

	memset(c, 0, 4016 * sizeof(int));

	lena = strlen(numA); lenb = strlen(numB);
	for (i = 0; i < lena; i++) a[lena - i-1] = numA[i] - '0';
	for (i = 0; i < lenb; i++) b[lenb - i-1] = numB[i] - '0';

	for (i = 0; i < lena; i++)
	{
		x = 0;
		for (j = 0; j < lenb; j++)/*对乘数的每一位进行处理*/
		{
			c[i + j] = a[i] * b[j] + x + c[i + j];/*当前乘积+上次乘积进位+原数*/
			x = c[i + j] / 10;
			c[i + j] %= 10;
		}
		c[i + lenb] = x;
	}

	lenc = lena + lenb;
	while (c[lenc - 1] == 0 && lenc > 1)/*删除前导0*/
		lenc--;
	j = 0;
	for (i = lenc - 1; i >= 0; i--)
	{
		//printf("%d_", c[i]);
		numA[j] = c[i] + '0', j++;
	}
}

int LLLcmp(char* a, char* b)
{
	int len1 = strlen(a), len2 = strlen(b);
	if (len1 < len2)return -1;
	else if (len1 > len2)return 1;

	for (int i = 0; i < len1; i++)
	{
		if (a[i] < b[i])return -1;
		else if (a[i] > b[i])return 1;
	}
	return 0;
}

// 求出str算式的值
void GetVal(const char* str)
{
	char plus[2008] = {0}, minus[2008] = { 0 };

	/*plus 和 minus 分别表示加(减)几次*/
	long long len = strlen(str);
	/*
	* flag 标识当前计算的是括号内的数字还是括号外的
	* num 储存括号外的数 tmpn 储存括号内的数
	*/
	long long flag = 0;
	char num[2008] = { 0 }, tmpn[2008] = { 0 };

	for (int i = 0; i < len; i++)
	{
		if (str[i] == '+')
		{
			pluss(plus, "1");
		}
		else if (str[i] == '-')
		{
			pluss(minus, "1");
		}
		else if (str[i] == '(')
		{
			flag = 1;
		}
		else if (str[i] == ')')
		{
			flag = 0;
		}
		else if ('0' <= str[i] && str[i] <= '9')
		{
			/*计算数字*/
			if (flag)
			{
				//tmpn = tmpn * 10 + str[i] - '0';
				int e = strchr(str, ')') - str;
				//printf("%d->%d__", i, e);
				for (int j = i; j < e; j++)
				{
					tmpn[j - i] = str[j];
				}
				//printf("%s_______\n",tmpn);
				flag = 0;
				i = e;
			}
			else
			{
				//num = num * 10 + str[i] - '0';
				for (int j = i; j < len; j++)
				{
					num[j - i] = str[j];
				}
				break;
			}
		}
	}

	if (tmpn[0])minuss(tmpn, "1", tmpn);
	
	//printf("%s %s\n", tmpn, num);

	if (plus[0])/*如果是加*/
	{	
		pluss(plus, tmpn);
		
		//printf("|%s*%s|_\n", num, plus);

		cf(num, plus);
		if (ans.flag == 0)
		{
			pluss(ans.num, num);
		}
		else
		{
			int tmp = LLLcmp(ans.num, num);
			if (tmp == 0)
			{
				ans.flag = 0;
				ans.num[0] = '0';
				ans.num[1] = '\0';
			}
			else if (tmp > 0)
			{
				ans.flag = 1;
				minuss(ans.num, num, ans.num);
			}
			else if (tmp < 0)
			{
				//printf("%s %s\n", ans.num, num);
				ans.flag = 0;
				minuss(num, ans.num, ans.num);

			}
		}
	}
	else/*否则是减*/
	{
		pluss(minus, tmpn);
		//printf("|%s|\n|%s|_\n", num, minus);

		cf(num, minus);

		if (ans.flag == 1)
		{
			pluss(ans.num, num);
		}
		else
		{
			int tmp = LLLcmp(ans.num, num);
			if (tmp == 0)
			{
				ans.flag = 0;
				ans.num[0] = '0';
				ans.num[1] = '\0';
			}
			else if (tmp > 0)
			{
				ans.flag = 0;
				minuss(ans.num, num, ans.num);
			}
			else if (tmp < 0)
			{
				//printf("a:%s n:%s\n", ans.num, num);
				ans.flag = 1;
				minuss(num, ans.num, ans.num);
			}
		}
	}
}

int main()
{
	ans.flag = 0;

	// 因为要靠运算符进行标识,所以需要在前后端添加符号

	scanf("%s", &(str[1]));// 直接从第一位开始输入
	if (str[1] != '+' && str[1] != '-')str[0] = '+';// 避免重复
	else str[0] = ' ';
	int len = strlen(str);
	str[len] = '+';
	//str[len+1]='\0';// 在全局定义的数组默认初始化为0

	for (int i = 0; i < len; i++)
	{
		if (str[i] == '+' || str[i] == '-') // 找到运算符
		{
			for (int j = i + 1; j < len; j++) // 开始找结束位置
			{
				if (str[j] == '+' || str[j] == '-')
				{
					if (str[j - 1] != '+' && str[j - 1] != '-')
					{
						for (int k = i; k < j; k++)stmp[k - i] = str[k];// 拷贝这一段字符串
						stmp[j - i] = 0;

						GetVal(stmp); // 处理这一段算式
						i = j - 1; // 跳到下一段
						break;
					}
				}
			}
		}
	}

	if (ans.flag==1)putchar('-');
	printf("%s", ans.num);
	return 0;
}
```
###### 乌拉乌拉~~

---

## 作者：流逝丶 (赞：8)

原AC代码已更改，感谢@Treaker提供的数据

首先看题，只有+，-，*。

考虑开long long直接搞

首先当做字符串读入

其中总共有五种类别

1.一开始只有一个数字

2.+（x）y

3.+++……+x

4.-（x）y

5.---…-x

读入数字的话考虑将快读更改
```cpp
inline int read(int x){//x表示当前位置
	int s=0;
	while(ch[x]<'0'||ch[x]>'9')x++;//非数字
	while(ch[x]>='0'&&ch[x]<='9')s=s*10+ch[x]-'0',x++;
	return s;
}
```
开个ans记录答案，判断每种运算累积到ans中，最后输出ans。

```cpp
for(int i=1;i<=len;++i){
		if(ch[i]=='+'&&ch[i+1]=='('){	//当前为第2种运算 
			int k=read(i+2);			//跳过左括号读入括号内数字 
			while(ch[i]<'0'||ch[i]>'9')i++;
			while(ch[i]>='0'&&ch[i]<='9')i++;
			i++;						//跳过右括号 
			ans+=read(i)*k;				//读入数字及进行乘法运算累积ans 
		}
		else if(ch[i]=='-'&&ch[i+1]=='('){//当前为第4种运算 
			int k=read(i+2);			
			while(ch[i]<'0'||ch[i]>'9')i++;
			while(ch[i]>='0'&&ch[i]<='9')i++;
			i++;
			ans-=read(i)*k;
		}
		else if(ch[i]=='+'&&ch[i+1]>='0'&&ch[i+1]<='9'){//当前为第3种运算特殊情况 
			ans+=read(i+1);				//只有一个加号 
		}
		else if(ch[i]=='-'&&ch[i+1]>='0'&&ch[i+1]<='9'){//当前为第5种运算特殊情况 
			ans-=read(i+1);
		}
		else if(ch[i]=='+'&&ch[i+1]=='+'){//当前为第3种运算
			int cnt=0;					//多个加号记录加号个数 
			while(ch[i]=='+')cnt++,i++;
			ans+=read(i)*cnt;			//多加法运算转乘及累积答案 
		}
		else if(ch[i]=='-'&&ch[i+1]=='-'){//当前为第5种运算
			int cnt=0;
			while(ch[i]=='-')cnt++,i++;
			ans-=read(i)*cnt;
		}
		else if(i==1&&ch[i]>='0'&&ch[i]<='9')//第1种运算 
				ans=read(i);			
	}
```


然后60分就到手了。

答案太大炸了long long。

将原程序改写为高精，然后我们需要高精加，高精减，高精乘。

a1，a2数组表示暂时读入的两个数

将原读入函数更改，分成两个，一个读a1，另一个读a2，这里只提供第一个。


```cpp
inline void read1(int x){
	memset(a1,0,sizeof(a1));
	while(ch[x]<'0'||ch[x]>'9')x++;
	while(ch[x]>='0'&&ch[x]<='9')x++;
	x--;
	while(ch[x]>='0'&&ch[x]<='9')a1[++a1[0]]=ch[x]-'0',x--;
}
```

然后计算加减乘的时候大力讨论ans正负问题，ans的正负是打标记实现，正加正直接加；正加负变成正减正；负加负，改为正加正，标记不变；负减负变成正减负；

在加的时候符号是不变的，减的时候需要判断符号。

下面是完整AC代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char ch[210];
int a1[2000],a2[2000],sum[2000];//a1,a2暂时储存，sum储存乘出来的值 
int s[20000],ans[20000];
int f=1;


//读入 
inline void read1(int x){
	memset(a1,0,sizeof(a1));
	while(ch[x]<'0'||ch[x]>'9')x++;
	while(ch[x]>='0'&&ch[x]<='9')x++;
	x--;
	while(ch[x]>='0'&&ch[x]<='9')a1[++a1[0]]=ch[x]-'0',x--;
}
inline void read2(int x){
	memset(a2,0,sizeof(a2));
	while(ch[x]<'0'||ch[x]>'9')x++;
	while(ch[x]>='0'&&ch[x]<='9')x++;
	x--;
	while(ch[x]>='0'&&ch[x]<='9')a2[++a2[0]]=ch[x]-'0',x--;
}



//高精乘 
inline void mul(){
	sum[0]=a1[0]+a2[0]-1;
	for(int j=1;j<=a2[0];j++){
        for(int i=1;i<=a1[0];i++){
            sum[i+j-1]+=a1[i]*a2[j];
            sum[i+j]+=sum[i+j-1]/10;
            sum[i+j-1]%=10;
        }
    }
    if(sum[sum[0]+1]>=1) sum[0]++;
    while(sum[sum[0]]==0&&sum[0]>1)--sum[0];
}

//高精加 
inline void add(int a[],int b[]){
    memset(s,0,sizeof(s));
    int len=max(a[0],b[0]);
    int g=0;
    for(int i=1;i<=len;i++){
        s[i]+=a[i]+b[i]+g;
        g=s[i]/10;
        s[i]=s[i]%10;
    }
    if(g)s[++len]=g;
    s[0]=len;
    for(int i=0;i<=len;++i)ans[i]=s[i];
}

//高精减 
inline bool com(int a[],int b[]){
	if(a[0]>b[0])return 0;
	if(a[0]<b[0])return 1;
    for(int i=a[0];i>=1;--i){
    	if(a[i]<b[i])return 1;
    	if(a[i]>b[i])return 0;
    }
    return 0;
}
inline void jian(int a[],int b[]){
	if(com(a,b)){
		swap(a,b);
		f=-1;
	}
	else f=1;
    for(int i=1;i<=a[0];++i){
    	if(i<=b[0])   //我不知道为啥可能在i<=a[0]&&i>=b[0]的时候b[i]有值
    		a[i]-=b[i];
    	if(a[i]<0){
    		a[i]+=10;
    		a[i+1]--;
    	}
    }
    while(a[a[0]]==0&&a[0]>1)a[0]--;
    for(int i=0;i<=a[0];++i)
    	ans[i]=a[i];
}

//把int型数拆到数组中 
inline void dig(int x){
	memset(a1,0,sizeof(a1));
	while(x){
		a1[++a1[0]]=x%10;
		x/=10;
	}
}
int main(){
	scanf("%s",ch+1);
	int len=strlen(ch+1);
	for(int i=1;i<=len;++i){
		if(ch[i]=='+'&&ch[i+1]=='('){
			read1(i+2);
			while(ch[i]<'0'||ch[i]>'9')i++;
			while(ch[i]>='0'&&ch[i]<='9')i++;
			i++;
			read2(i);
			mul();
			if(f==1)			//讨论符号，f为1，ans为正，f为-1，ans为负 
				add(ans,sum);
			else jian(sum,ans);
			memset(sum,0,sizeof(sum));
		}
		else if(ch[i]=='-'&&ch[i+1]=='('){
			read1(i+2);
			while(ch[i]<'0'||ch[i]>'9')i++;
			while(ch[i]>='0'&&ch[i]<='9')i++;
			i++;
			read2(i);
			mul();
			if(f==1)
				jian(ans,sum);
			else add(ans,sum);
			memset(sum,0,sizeof(sum));
		}
		else if(ch[i]=='+'&&ch[i+1]>='0'&&ch[i+1]<='9'){
			read1(i+1);
			if(f==1)
			add(ans,a1);
			else jian(a1,ans);
		}
		else if(ch[i]=='-'&&ch[i+1]>='0'&&ch[i+1]<='9'){
			read1(i+1);
			if(f==1)jian(ans,a1);
			else add(ans,a1);
		}
		else if(ch[i]=='+'&&ch[i+1]=='+'){
			int cnt=0;
			while(ch[i]=='+')cnt++,i++;
			dig(cnt);
			read2(i);
			mul();
			if(f==1)add(ans,sum);
			else jian(sum,ans);
			memset(sum,0,sizeof(sum));
		}
		else if(ch[i]=='-'&&ch[i+1]=='-'){
			int cnt=0;
			while(ch[i]=='-')cnt++,i++;
			dig(cnt);
			read2(i);
			mul();
			if(f==1)
				jian(ans,sum);
			else add(ans,sum);
			memset(sum,0,sizeof(sum));
		}
		else if(i==1&&ch[i]>='0'&&ch[i]<='9'){
			read1(i);
			for(int j=0;j<=a1[0];++j)
				ans[j]=a1[j];
		}
	}
	if(f==-1)printf("-");
	for(int i=ans[0];i>0;--i)
		printf("%d",ans[i]);
	return 0;
}
```




---

## 作者：Treaker (赞：6)

这个题高精还是比较简单的，就是读入比较恶心（卡了1天），注意一下读入就行了。
没什么难的。
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define N (5555)
using namespace std;
char s[N];
int times[N][N] , num[N][N] , ans[N] , tmp[N] , temp[N];
int cnt;
bool flag[N] , ccf[N];
bool goal;
bool check(int *a,int *b)
{
	if(a[0] > b[0])	return 1;
	if(a[0] < b[0]) return 0;
	for(int i = a[0];i >= 1;i --)
	{
		if(a[i] > b[i]) return 1;
		if(a[i] < b[i]) return 0;
	}
	return 1;
}
void jia(int *a,int *b)
{
	memset(temp,0,sizeof temp);
	bool qwq = check(a,b);
	if(qwq)
	{
		for(int i = 0;i <= a[0];i ++)	temp[i] = a[i];
		for(int i = 1;i <= temp[0];i ++)
		{
			temp[i] += b[i];
			temp[i + 1] += temp[i] / 10;
			temp[i] %= 10;
		}
		if(temp[temp[0] + 1])	temp[0] ++;
	}
	else
	{
		for(int i = 0;i <= b[0];i ++)	temp[i] = b[i];
		for(int i = 1;i <= temp[0];i ++)
		{
			temp[i] += a[i];
			temp[i + 1] += temp[i] / 10;
			temp[i] %= 10;
		}
		if(temp[temp[0] + 1]) temp[0] ++;
	}
}
void jian(int *a,int *b)
{
	memset(temp,0,sizeof temp);
	for(int i = 1;i <= a[0];i ++)	temp[i] = a[i];
	temp[0] = a[0];
	for(int i = 1;i <= temp[0];i ++)
	{
		if(temp[i] < b[i])	temp[i] += 10 , temp[i+1] --;
		temp[i] -= b[i];
	}
}
void cheng(int *a,int *b)
{
	memset(tmp,0,sizeof tmp);
	for(int i = 1;i <= a[0];i ++)
	{
		for(int j = 1;j <= b[0];j ++)
		{
			tmp[i + j - 1] += a[i] * b[j];
			tmp[i + j] += tmp[i + j - 1] / 10;
			tmp[i + j - 1] %= 10;
		}
	}
	if(tmp[a[0] + b[0]]) tmp[0] = a[0] + b[0];
	else tmp[0] = a[0] + b[0] - 1;
}
int main()
{
	scanf("%s",s+1);
	int len = strlen(s+1) , tot = 0;
	for(int i = 1;i <= len;i ++)	
	{
		if(s[i] != '0')	break;
		else tot ++;
	}
	len -= tot;
	for(int i = 1;i <= len;i ++)	s[i] = s[i + tot];
	for(int i = 1;i <= len;i ++)
	{
		int j , qwq = 0;
		if(s[i] >= '0' && s[i] <= '9' && i == 1)
		{
			times[++cnt][1] = 1;
			times[cnt][0] = 1;
			for(j = i;j <= len && s[j] >= '0' && s[j] <= '9';j ++)	num[cnt][++num[cnt][0]] = s[j] - '0';
			i = j - 1;
			continue;
		}
		if(s[i] == '(')
		{
			cnt ++;
			for(j = i + 1;j <= len && s[j] != ')';j ++)	times[cnt][++times[cnt][0]] = s[j] - '0';
			if(s[i-1] == '-')	flag[cnt] = 1;
			i = j;
		}	
		if((s[i] == '+' || s[i] == '-') && s[i + 1] == '(')	continue;
		if(s[i] >= '0' && s[i] <= '9' && (s[i-1] == '+' || s[i-1] == '-'))		
		{
			cnt ++;
			for(j = i - 1;j >= 1 && s[j] == s[i-1];j --) qwq ++;
			while(qwq)	times[cnt][++times[cnt][0]] = qwq % 10 , qwq /= 10;
			if(s[i-1] == '-')	flag[cnt] = 1;
			ccf[cnt] = 1;
		}
		if(s[i] >= '0' && s[i] <= '9' && i != 1)	
		{
			for(j = i;j <= len && s[j] >= '0' && s[j] <= '9';j ++)	num[cnt][++num[cnt][0]] = s[j] - '0';
			i = j - 1;
		}
	}
	for(int i = 1;i <= cnt;i ++)
	{
		for(int j = 1;j <= (times[i][0] >> 1);j ++)	if(!ccf[i])  swap(times[i][j],times[i][times[i][0] - j + 1]);
		for(int j = 1;j <= (num[i][0] >> 1);j ++)	swap(num[i][j],num[i][num[i][0] - j + 1]);
	}
	for(int i = 1;i <= cnt;i ++)
	{
		for(int j = times[i][0];j >= 1;j --)	
		{
			if(times[i][j] != 0)	break;
			times[i][0] --;
		}
		for(int j = num[i][0];j >= 1;j --)	
		{
			if(num[i][j] != 0)	break;
			num[i][0] --;
		}
		cheng(times[i],num[i]);
		for(int j = tmp[0];j >= 1;j --)	
		{
			if(tmp[j] != 0)	break;
			tmp[0] --;
		}
		if(!goal && !flag[i])	jia(ans,tmp);
		else if(goal && flag[i])	jia(ans,tmp);
		else if(!goal && flag[i] && check(ans,tmp))	jian(ans,tmp);
		else if(!goal && flag[i] && !check(ans,tmp))	jian(tmp,ans) , goal = 1;
		else if(goal && !flag[i] && check(ans,tmp))	jian(ans,tmp);
		else if(goal && !flag[i] && !check(ans,tmp)) jian(tmp,ans) , goal = 0;
		for(int j = 0;j <= temp[0];j ++)	ans[j] = temp[j];
		for(int j = ans[0];j >= 1;j --)	
		{
			if(ans[j] != 0)	break;
			ans[0] --;
		}
	}
	bool cnm = 0 , fuck = 0;
	for(int i = ans[0];i >= 1;i --)	if(ans[i] != 0)	fuck = 1;
	if(goal && fuck) printf("-");
	for(int i = ans[0];i >= 1;i --)	
	{
		if(ans[i] != 0)	cnm = 1;
		else if(!cnm)	continue;
		printf("%d",ans[i]);
	}
	if(!ans[0] || !cnm)	printf("0");
	return 0;
}
```


---

## 作者：critnos (赞：4)

> ~~是谷民改不了水高精~~

因为这题要用高精度，所以~~自然而然地~~就想到用 python 做了。

分类讨论，先判断是“---”一类的运算还是“+(3)”一类的运算。

然后就是基础字符串操作了。

对于第一种（“---”一类的运算），统计有多少个“+”/“-”号，然后直接用乘法计算。

对于第二种（“+(3)”一类的运算），截取出括号中间的数，同样用乘法计算。

python 有一个好用的函数：

```python
int()
```
可以直接把一段字符串转成整数进行计算，配合 python 简短的字符串截取功能，可以轻松通过本题。

~~为什么我感觉这题就是为了 PY 而生的啊~~

```python
a=input()
i,s=0,0
while i<len(a):
    if a[i]=='+': #判断正负号
        f=1
    else:
        f=-1
    if a[i+1]=='(':
        i=i+2
        y=i
        while i<len(a) and a[i]!=')':
            i=i+1
        x=int(a[y:i]) #字符串截取
        i=i+1
        y=i
        while i<len(a) and a[i]!='+' and a[i]!='-':
            i=i+1
        s=s+x*int(a[y:i])*f #神奇的操作
    else:
        y=0
        while i<len(a) and (a[i]=='+' or a[i]=='-'):
            i=i+1
            y=y+1
        x=i
        while i<len(a) and a[i]!='+' and a[i]!='-':
            i=i+1
        s=s+y*int(a[x:i])*f
print(s,end='') #删去空行
```
**注意这题的末行不能有多余的空行。**

---

## 作者：Alarm5854 (赞：4)

这道题看上去是紫题，实际上只有蓝题的难度，而且得$40$分非常容易，所以为了对那些不会高精度的新手友好一点，我写两个做法~~其实是因为我第一次交也只有40分~~。
### 40pts:
做这道题只需要统计一下$+$，$-$的个数，并且把字符串转为数字，而这是非常容易的，对于乘法也如法炮制，这样就有$40$分了：
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    char op[2100];
    int num[2100],i,j,k,s,ans,flag;
    void turn(int s,int t,int &a)//字符转数字
    {
        a=0;
        for(int i=s;i<t;i++)
            a*=10,a+=op[i]-48;
    }
    int main()
    {
        scanf("%s",op);
        while(op[i]!='\0')
        {
            while(op[i]=='+') flag=1,s++,i++;//处理加法，看有多少加号
            while(op[i]=='-') flag=-1,s++,i++;//处理减法，看有多少减号
            if(isdigit(op[i]))//下一个就是数字
            {
                j=i;
                while(isdigit(op[j]))
                    j++;
                turn(i,j,num[++k]);//直接转换
                num[k]*=s*flag;//乘上前面加的次数
                i=j,s=0;
            }
            else
            {
                if(op[i]=='(')//否则，下一个就是括号
                {
                    i++;j=i;
                    while(isdigit(op[j]))
                        j++;
                    turn(i,j,s);//把累加器更新
                    i=j;
                }
                if(op[i]==')')
                    i++;
            }
        }
        for(int i=1;i<=k;i++)
            ans+=num[i];//一个一个加起来
        printf("%d",ans);//输出
        return 0;
    }
```
### 100pts:
但是，如果想拿$100$分，就需要下工夫了，高精度是必备的，不懂的人可以看一下我的[高精度模板](https://www.luogu.org/blog/YCE-22/gao-jing-du-mu-ban)，这里有很多的运算，可以把它当做低精做，就是代码太长了：
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    struct ll{//我喜欢把高精度定义成一个结构体
        char s[2100];
        int a[2100],flag;
        void clear()
        {
            memset(s,0,sizeof(s));
            memset(a,0,sizeof(a));
            *a=1,flag=1;
        }
        void out()
        {
            /*if(!flag)
            {
                puts("INF"),flag=1;
                return;
            }*/
            if(!~flag) printf("-");//处理负数
            for(int i=*a;i;--i)
                printf("%d",a[i]);
            puts("");
        }
        void sin(long long x)//化低精为高精
        {
            clear(),a[0]=0;
            if(x<0) flag=-1,x=-x;
            else flag=1;
            while(x)
                a[++*a]=x%10,x/=10;
        }
        int& operator [](const int &n)//用数组运算符，方便访问高精度元素
        {
            if(!~n) return flag;
            return a[n];
        }
        /*a[-1]表示a的正负性，1为正，-1为负。a[0]表示a的位数。其他情况下表示a的第n位。*/
    };
    char op[2100];
    int i,j,k,flag;
    ll num[2100],ans,s;
    bool operator <(ll a,ll b);//声明语句一定不能少
    bool operator >(ll a,ll b);
    ll operator +(ll a,ll b);//高精度的运算
    ll operator -(ll a,ll b);
    ll operator *(ll a,ll b);
    bool operator <(ll a,ll b)
    {
        if(!~a[-1]&&~b[-1]) return 1;
        if(~a[-1]&&!~b[-1]) return 0;
        if(!~a[-1]&&!~b[-1])
        {
            a[-1]=b[-1]=1;
            return a>b;
        }
        if(a[0]<b[0]) return 1;
        if(a[0]>b[0]) return 0;
        for(int i=a[0];i>0;--i)
        {
            if(a[i]<b[i]) return 1;
            if(a[i]>b[i]) return 0;
        }
        return 0;
    }
    bool operator >(ll a,ll b)
    {
        if(!~a[-1]&&~b[-1]) return 0;
        if(~a[-1]&&!~b[-1]) return 1;
        if(!~a[-1]&&!~b[-1])
        {
            a[-1]=b[-1]=1;
            return a<b;
        }
        if(a[0]<b[0]) return 0;
        if(a[0]>b[0]) return 1;
        for(int i=a[0];i>0;--i)
        {
            if(a[i]<b[i]) return 0;
            if(a[i]>b[i]) return 1;
        }
        return 0;
    }
    ll operator +(ll a,ll b)
    {
        ll c;
        c.clear();
        if(!~a[-1]&&!~b[-1])
        {
            a[-1]=b[-1]=1;
            c=a+b,c[-1]=-1;
            return c;
        }
        if(!~a[-1])
        {
            a[-1]=1;
            c=b-a;
            return c;
        }
        if(!~b[-1])
        {
            b[-1]=1;
            c=a-b;
            return c;
        }
        c[0]=max(a[0],b[0]);
        for(int i=1;i<=c[0];++i)
            c[i]=a[i]+b[i];
        for(int i=1;i<=c[0];++i)
            c[i+1]+=c[i]/10,c[i]%=10;
        if(c[c[0]+1]) ++c[0];
        return c;
    }
    ll& operator +=(ll &a,ll &b)
    {
        a=a+b;
        return a;
    }
    ll operator -(ll a,ll b)
    {
        ll c;
        c.clear();
        if(!~a[-1])
        {
            a[-1]=1;
            c=a+b,c[-1]=-c[-1];
            return c;
        }
        if(!~b[-1])
        {
            b[-1]=1;
            c=a+b;
            return c;
        }
        if(a<b)
        {
            c=b-a,c[-1]=-1;
            return c;
        }
        c=a;
        for(int i=1;i<=c[0];++i)
        {
            c[i]-=b[i];
            if(c[i]<0)
                --c[i+1],c[i]+=10;
        }
        while(!c[c[0]]&&c[0]>1) --c[0];
    }
    ll operator *(ll a,ll b)
    {
        ll c;
        int x;
        c.clear();
        if(a[-1]!=b[-1])
        {
            a[-1]=b[-1]=1;
            c=a*b,c[-1]=-1;
            return c;
        }
        c[0]=a[0]+b[0],a[-1]=b[-1]=1;
        for(int i=1;i<=a[0];++i)
        {
            x=0;
            for(int j=1;j<=b[0];++j)
            {
                c[i+j-1]+=a[i]*b[j]+x;
                x=c[i+j-1]/10;
                c[i+j-1]%=10;
            }
            c[i+b[0]]=x;
        }
        while(!c[c[0]]&&c[0]>1) --c[0];
        return c;
    }
    ll operator +(ll a,long long b)//高精与低精的运算
    {
        ll x;
        x.sin(b);
        return a+x;
    }
    ll operator -(ll a,long long b)
    {
        ll x;
        x.sin(b);
        return a-x;
    }
    ll operator *(ll a,long long b)
    {
        ll x;
        x.sin(b);
        return a*x;
    }
    ostream& operator <<(ostream& os,ll &x)//定义输出流，方便输出
    {
        x.out();
        return os;
    }
    void turn(int s,int t,ll &a)//前面都是高精度的定义
    {
        a.clear();
        for(int i=s;i<t;++i)
            a=a*10,a=a+op[i]-48;
    }
    int main()//主函数的解释在40分做法里已经提过了，我就不再解释一遍了
    {
        scanf("%s",op);
        while(op[i]!='\0')
        {
            while(op[i]=='+') flag=1,s=s+1,++i;
            while(op[i]=='-') flag=-1,s=s+1,++i;
            if(isdigit(op[i]))
            {
                j=i;
                while(isdigit(op[j]))
                    ++j;
                turn(i,j,num[++k]);
                num[k]=num[k]*s*flag;
                i=j,s.clear();
            }
            else
            {
                if(op[i]=='(')
                {
                    j=++i;
                    while(isdigit(op[j]))
                        ++j;
                    turn(i,j,s);
                    i=j;
                }
                if(op[i]==')')
                    ++i;
            }
        }
        for(int i=1;i<=k;i++)
            ans+=num[i];
        cout<<ans;//用cout输出即可
        return 0;
    }
```
我发的题解是从来也不挖坑的，请大家自觉，抵制抄题解这种不良习惯，谢谢。

---

## 作者：Von_Brank (赞：4)

这题是[@laybxc](https://www.luogu.org/space/show?uid=51441)这位神犇推荐给我写的。从开始写到AC前后时间跨度一个星期，这是我第一次认认真真写高精，100+的总提交次数应该有15次是我提交的，因为实在太毒瘤了，感谢@laybxc提供的高精度模板让我找出了原本我写的代码中的错误，今天终于AC了，所以发一篇题解庆祝一下。

--------------------------------------------------------

这道题本质是道模拟题（第一次看的时候还是黄题，现在居然蓝了），主要做法就是遍历字符串并找出每一项的值，然后加起来，用int可以过60分，long long和int128也都只能过60分，显然剩下40分必须用高精了。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
//因为我太弱了，不会写高精度类，只会用struct
//而且写高精度算法的经验比较少，所以高精写的比较丑
struct BigInt	
{
    int ch;
    int x[300];
};
inline void clear(BigInt& x);		//初始化BigInt
inline BigInt read();				//读入BigInt（好像这题并没有用）
inline int Compare(BigInt a, BigInt b);//比较函数
inline BigInt Plus(BigInt a, BigInt b);//高精加
inline BigInt Minus(BigInt a, BigInt b);//高精减
inline BigInt Multi(BigInt a, BigInt b);//高精乘
inline BigInt Int_to_BigInt(int x);//把int转换成BigInt
inline void clear(BigInt& x)
{
    memset(x.x, 0, sizeof(x.x));
    x.ch = 1;
}
inline BigInt read()
{
    BigInt x;
    clear(x);
    char ch = getchar();
    while(!isdigit(ch) && ch != '-')
        ch = getchar();
    if(ch == '-')
    {
        x.ch = -1;
        ch = getchar();
    }
    while(isdigit(ch))
    {
        x.x[++x.x[0]] = ch - '0';
        ch = getchar();
    }
    for(int i=1; i<=x.x[0]/2; i++)
    {
        swap(x.x[i], x.x[x.x[0]-i+1]);
    }
    return x;
}
inline BigInt Int_to_BigInt(int x)
{
    BigInt c;
    clear(c);
    if(x < 0)
    {
        c.ch = -1;
        x = -x;
    }
    if(x == 0) c.x[0]++;
    while(x)
    {
        c.x[++c.x[0]] = x % 10;
        x /= 10;
    }
    return c;
}
inline int Compare(BigInt a, BigInt b)
{
    if(a.x[0] > b.x[0]) return 1;
    if(a.x[0] < b.x[0]) return -1;
    for(int i=a.x[0]; i; i--)
    {
        if(a.x[i] > b.x[i]) return 1;
        if(a.x[i] < b.x[i]) return -1;
    }
    return 0;
}
inline BigInt Plus(BigInt a, BigInt b)
{
    BigInt c;
    clear(c);
    if(a.ch == 1 && b.ch == -1)
    {
        b.ch = 1;
        return Minus(a, b);
    }
    if(a.ch == -1 && b.ch == 1)
    {
        a.ch = 1;
        return Minus(b, a);
    }
    if(a.ch == -1 && b.ch == -1)
    {
        c.ch = -1;
    }
    int k = a.x[0] > b.x[0] ? a.x[0] : b.x[0], g = 0;
    for(int i=1; i<=k; i++)
    {
        c.x[i] = a.x[i] + b.x[i] + g;
        g = c.x[i] / 10;
        c.x[i] %= 10;
    }
    if(g) c.x[++k] = g;
    c.x[0] = k;
    return c;
}
inline BigInt Minus(BigInt a, BigInt b)
{
    BigInt c;
    clear(c);
    if(a.ch == -1 && b.ch == -1)
    {
        a.ch = 1;
        b.ch = 1;
        return Minus(b, a);
    }
    if(a.ch == -1 && b.ch == 1)
    {
        a.ch = 1;
        c = Plus(a, b);
        c.ch = -1;
        return c;
    }
    if(a.ch == 1 && b.ch == -1)
    {
        b.ch = 1;
        return Plus(a, b);
    }
    int flag = Compare(a, b);
    if(flag == 0)
    {
        c.x[0] = 1;
        return c;		
    }
    if(flag == 1)
    {
        int k = a.x[0];
        for(int i=1; i<=k; i++)
        {
            if(a.x[i] < b.x[i])
            {
                a.x[i+1]--;
                a.x[i] += 10;
            }
            c.x[i] = a.x[i] - b.x[i];
        }
        while(c.x[k] == 0) k--;
        c.x[0] = k;
        return c;
    }
    else
    {
        int k = b.x[0];
        c.ch = -1;
        for(int i=1; i<=k; i++)
        {
            if(b.x[i] < a.x[i])
            {
                b.x[i+1]--;
                b.x[i] += 10;
            }
            c.x[i] = b.x[i] - a.x[i];
        }
        while(c.x[k] == 0) k--;
        c.x[0] = k;
        return c;
    }
}
inline BigInt Multi(BigInt a, BigInt b)
{
    BigInt c;
    clear(c);
    c.ch = a.ch * b.ch;
    int ka = a.x[0], kb = b.x[0], k = ka + kb + 1;
    for(int i=1; i<=ka; i++)
    {
        for(int j=1; j<=kb; j++)
        {
            c.x[i+j-1] += a.x[i] * b.x[j];
            c.x[i+j] += c.x[i+j-1] / 10;
            c.x[i+j-1] %= 10;
        }
    }
    while(!c.x[k]) k--;
    c.x[0] = k;
    return c;
}
inline void print(BigInt x)//打印高精度数
{
    if(x.x[0] == 0) printf("0");
    if(x.ch == -1) printf("-");
    for(int i=1; i<=x.x[0]; i++)
        printf("%d", x.x[x.x[0]-i+1]);
}
const int maxn = 205;
int top, len;
int b[maxn];
BigInt ansx, ans[maxn], tmp;
char a[maxn];
int main()
{
    clear(ansx);
    ansx.x[0] = 1;
    scanf("%s", a+1);
    len = strlen(a+1);
    for(int i=1; i<=len; i++)
    {
        if(i == 1 && (a[i] >= '0' && a[i] <= '9'))
        {	//如果第一个字符属于第一个数，则直接存起来
            int l, r;
            for(l=1; l<=len; l++)
            {
                if(a[l] < '0' || a[l] > '9')
                {
                    r = l-1;
                    break;
                }
            }
            ++top;
            clear(ans[top]);
            ans[top] = Plus(ans[top], Int_to_BigInt(a[1] - '0'));
            for(int j=2; j<=r; j++)
            {
            	clear(tmp);
            	ans[top] = Multi(ans[top], Int_to_BigInt(10));
                ans[top] = Plus(ans[top], Int_to_BigInt(a[j]-'0'));
            }
            continue;
        }
        if(a[i] == '+' || a[i] == '-')
        {	//遇到'+'号或'-'号就处理这一项的值
            char character;
            character = a[i];
            int m, k, l;
            BigInt ax, bx, numc;
            clear(ax);
            clear(bx);
            clear(numc);
            for(int j=i; j<=len; j++)
            {	//找出'+'号或'-'号的个数
                if(a[j] != character)
                {
                    m = j - 1;
                    break;
                } 
                numc = Plus(numc, Int_to_BigInt(1));
            }
            if(a[m+1] == '(')
            {	//处理括号内的数的值
                for(int j=m+2; j<=len; j++)
                {
                    if(a[j] == ')')
                    {
                        k = j-1;
                        break;
                    }
                }
                ax = Plus(ax, Int_to_BigInt(a[m+2] - '0'));
                for(int j=m+3; j<=k; j++)
                {
                	ax = Multi(ax, Int_to_BigInt(10));
                    ax = Plus(ax, Int_to_BigInt(a[j] - '0'));
                }				
            }
            else
            {
                k = m - 1;
                ax = Plus(Int_to_BigInt(0), Int_to_BigInt(1));
                //如果并没有括号则 ax = 1;
            }
            for(int j=k+2; j<=len; j++)
            {	//处理此项剩余部分的值
                if(j == len) l = j;
                if(a[j] < '0' || a[j] > '9')
                {
                    l = j-1;
                    break;
                }
            }
            bx = Plus(bx, Int_to_BigInt(a[k+2] - '0'));
            for(int j=k+3; j<=l; j++)
            {
            	bx = Multi(bx, Int_to_BigInt(10));
                bx = Plus(bx, Int_to_BigInt(a[j] - '0'));
            }
            ++top;
            clear(ans[top]);
            ans[top] = Plus(Int_to_BigInt(0), Int_to_BigInt(1));
            ans[top] = Multi(ans[top], ax);
            ans[top] = Multi(ans[top], bx);
            ans[top] = Multi(ans[top], numc);
            //把符号个数，括号内的数，后的数的值乘起来
            i = l;
            if(character == '-')//如果是'-'号则项取相反数
            	ans[top] = Multi(ans[top], Int_to_BigInt(-1));
        }
    }
    for(int i=1; i<=top; i++) //把每一项的数加起来作为答案输出
    	ansx = Plus(ansx, ans[i]);
    print(ansx);
    return 0;
}
```

---

## 作者：ppip (赞：3)

蒟蒻的第一篇题解，不足之处请大佬见谅。

[题目链接](https://www.luogu.com.cn/problem/P1557)

首先，数据范围是长度不超过2000，所以要开**高精度**。

根据题意，有加法，减法和乘法。所以先把高精度写完（我使用的是vector）。

加法高精度

```c++
vector<int> Plus(const vector<int>& a,const vector<int>& b)
{
	vector<int>c(max(a.size(),b.size())+1);
	for (int i=0;i<min(a.size(),b.size());++i)
		c[i]+=a[i]+b[i];
	if (a.size()>b.size())
	for (int i=b.size();i<a.size();++i)c[i]=a[i];
	else for (int i=a.size();i<b.size();++i)c[i]=b[i];
	for (int i=0;i<c.size()-1;++i)
	{
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if (!c[c.size()-1])c.pop_back(); //最高位为0
	return c;
}
```
减法高精度
```c++
vector<int> Minus(vector<int> a,vector<int> b) //a-b
{
	int cmpans=cmp(a,b); //这是比较两个数大小
	if (!cmpans) //相等的情况
	{
		vector<int>c;
		c.push_back(0);
		return c;
	}
	else if(cmpans==-1) //a<b
	{
		neg=!neg; //这是一个标签，记录是不是负数
		swap(a,b);
	}
	vector<int>c(max(a.size(),b.size()));
	for (int i=0;i<min(a.size(),b.size());++i)
		c[i]=a[i]-b[i];
	for (int i=b.size();i<a.size();++i)c[i]=a[i];
	for (int i=0;i<c.size()-1;++i)
	{
		if (c[i]<0)
		{
			--c[i+1];
			c[i]+=10;
		}
	}
	while (!c[c.size()-1])c.pop_back(); //最高位为0
	return c;	
}
```
乘法高精度
```c++
vector<int> mul(const vector<int>&a,const vector<int>&b)
{
	vector<int>c(a.size()+b.size());
	for (int i=0;i<a.size()+b.size();++i)c[i]=0;
	for (int x=0;x<a.size();++x)
	for (int y=0;y<b.size();++y)
	{
		c[x+y]+=a[x]*b[y]; //想想为什么
	}
	for (int i=0;i<c.size()-1;++i)
	{
		c[i+1]+=c[i]/10;
		c[i]%=10;
	}
	if (!c[c.size()-1])c.pop_back(); //最高位为0
	return c;
}
```
接下是字符串处理。

方法：将整个字符串拆成表达式，每个表达式单独计算，最后加到ans里。

有以下几种情况：

$+++x$
---
计算有多少个加号，再读入数字，把他们乘起来。
```c++
charge(to,bit-i/*加号个数*/); //把to填充为加号个数
while (isdigit(s[i]))num.push_back(s[i]-'0'),++i;
reverse(num.begin(),num.end()); //因为读入是反着的，要把高低位反过来
num=mul(num,to); //乘起来
--i; //因为更新时会跳过一个字符，所以要后退一个
```
$+(x)x$
---
分别读入括号里的数和后面的数，再乘起来。
```c++
++i; //跳过加号
while (s[i]!=')')to.push_back(s[i]-'0'),++i;
reverse(to.begin(),to.end());
++i; //跳过右括号
while (isdigit(s[i]))num.push_back(s[i]-'0'),++i;
reverse(num.begin(),num.end());
num=mul(num,to);
--i;
```
$+x$
---
同多个加号（~~为什么一个加号要单独处理~~）
```c++
while (isdigit(s[i]))num.push_back(s[i]-'0'),++i;
reverse(num.begin(),num.end());
--i;
```
$x$
---
只有第一个表达式才会出现。（very easy）
```c++
while (isdigit(s[i]))num.push_back(s[i]-'0'),++i;
reverse(num.begin(),num.end());
--i;
```
余下三种：

$---x$

$-(x)x$

$-x$

同加法（太长不贴了）

---
终极问题：
## Q：如何把表达式加到ans里面？

A：字符串处理+分类讨论。

（r函数表示参数为（num，ans））
|ans符号|num符号|处理方法|
|---|---|--- |
| + | + |Plus|
| + | - |Minus(高精度已做正负处理)|
| - | + |rMinus，ans取相反数|
| - | - |Plus|

```c++
ans.push_back(0); //答案初始化为0
vector<int>num,to; //num是要加（减）的数，to是有多少个num相加（减）
for (int i=0;i<s.size();++i)
{
	num.clear();
	to.clear(); //初始化
	if (s[i]=='+') //加减法分开讨论
	{
		int bit=i;
		for (;s[i]=='+';++i); //记录有多少个加号
		//bit-i为加号个数
       		/*省略num处理过程（上面有）*/
               	//重点
		if (neg) ans=Minus(num,ans),neg=!neg; //判断ans是否为负，分开处理
		else ans=Plus(ans,num);
	}
	else if (s[i]=='-') //原理同加
	{
		//处理过程同加法，省去
		if (neg)ans=Plus(ans,num);
		else ans=Minus(ans,num);
	}
}
```

---

## 作者：Naptie (赞：3)

## [P1557](https://www.luogu.com.cn/problem/P1557) Java 版题解

由题可知，Kruscal 型算式的基本单元是
$$ +/-(a)\ b $$
或
$$ \overbrace{+\cdots}^{a}/\overbrace{-\cdots}^{a}\ b $$
其中，$a$ 和 $b$ 均代表**高精度整数**

为了方便，我们称上述两种基本单元分别为**括号单元**和**符链单元**

注意，一个算式的开头也有可能出现数字，比如题目中的 $\texttt{23+++15-2}$

明确这些之后，我们就可以开始了~

------------

0. **读入算式**
	```java
	String str = (new Scanner(System.in)).next();
	```

1. **处理数字开头的情况**

	一旦使用 `String` 中的 `startsWith(String prefix)` 方法发现算式的开头并不以运算符 `+` 或 `-` 开头，就将 `i` 自加，直到下标为 `i` 的字符是运算符为止

	同时将答案加上开头的数字
	```java
	int i = 0;
	BigInteger ans = BigInteger.ZERO;
	if (!str.startsWith("+") && !str.startsWith("-")) {
		while (str.charAt(i) != '+' && str.charAt(i) != '-') {
			i++;
		}
		ans = ans.add(new BigInteger(str.substring(0, i)));
	}
	```

2. **处理括号单元**

	在循环中，我们发现下标为 `i` 的字符是运算符，如果 `str.charAt(i + 1) == '('`，说明这个单元是一个形如 $ +/-(a)\ b $ 的括号单元

	目前下标 `i` 在运算符上，下标 `i + 1` 在“(”上，因此下标 `i + 2` 在 $a$ 的最高位（见下图）；我们只需通过 `while` 循环找到“)”的下标即可
    
	![Figure 1](https://i.postimg.cc/ZKmJQ0ky/Figure-1.png)
    
	找到之后，使用 `substring(int beginIndex, int endIndex)` 方法将 $a$ 截取出来，并储存为 `BigInteger`

	接下来，令 `i = ++j`，表示下标 `i` 在上图中 `j+1` 的位置，即 $b$ 的最高位；我们需要通过 `while` 循环找到下一个单元运算符的首位
    
	注意，如果当前单元是算式的最后一个单元，程序可能会抛出 `StringIndexOutOfBoundsException` 错误，导致 `Runtime Error`，我们需要使用 `try` 和 `catch` 进行捕捉并忽略
    
	截取 $b$ 之后，不仅要返回 $a ⋅ b$，还需要返回下一个单元的首位下标，这样就避免了主函数 `while` 循环中多余的查找，直接将此处的 `j` 赋值给主函数中的 `i` 即可
	```java
	// str 表示算式，i 表示某单元的首位下标
	private static Object[] bracket(String str, int i) {
		int j = i + 2;
		while (str.charAt(j) != ')') {
			j++;
		}
		BigInteger a = new BigInteger(str.substring(i + 2, j));
		i = ++j;
		try {
			while (str.charAt(j) != '+' && str.charAt(j) != '-') {
				j++;
			}
		} catch (StringIndexOutOfBoundsException ignored) {
		}
		BigInteger b = new BigInteger(str.substring(i, j));
		return new Object[]{a.multiply(b), j};
	}
	```

3. **处理符链单元**

	在循环中，我们发现下标为 `i` 的字符是运算符，如果 `str.charAt(i + 1) != '('`，说明这个单元是一个形如 $ \overbrace{+\cdots}^{a}/\overbrace{-\cdots}^{a}\ b $ 的符链单元（`i` 一定在某个单元的首位，因此如果这个单元是括号单元，则下标为 `i+1` 的字符一定是“(”；其他情况便是符链单元）

	使用 `while` 循环得到数字首次出现的位置，记为 `j`（只要 `str.charAt(j)` 是运算符就让 `j` 自加），则 $a = j - i$
    
	接下来，类似于处理括号单元，令 `i = ++j`，表示下标 `i` 在 $b$ 的最高位；我们需要通过 `while` 循环找到下一个单元运算符的首位
    
	注意，如果当前单元是算式的最后一个单元，程序可能会抛出 `StringIndexOutOfBoundsException` 错误，导致 `Runtime Error`，我们需要使用 `try` 和 `catch` 进行捕捉并忽略
    
	截取 $b$ 之后，不仅要返回 $a ⋅ b$，还需要返回下一个单元的首位下标，这样就避免了主函数 `while` 循环中多余的查找，直接将此处的 `j` 赋值给主函数中的 `i` 即可
	```java
	// str 表示算式，i 表示某单元的首位下标，op 表示运算符（+ 或 -）
	private static Object[] chain(String str, int i, char op) {
		int j = i;
		while (str.charAt(j) == op) {
			j++;
		}
		BigInteger a = new BigInteger((j - i) + "");
		i = j;
		try {
			while (str.charAt(j) != '+' && str.charAt(j) != '-') {
				j++;
			}
		} catch (StringIndexOutOfBoundsException ignored) {
		}
		BigInteger b = new BigInteger(str.substring(i, j));
		return new Object[]{a.multiply(b), j};
	}
	```

4. **输出答案**
	```java
	System.out.println(ans);
	```

------------

最后附上完整代码（真的很完整！）
```java
package me.naptie.oi;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		String str = (new Scanner(System.in)).next();
		int i = 0;
		BigInteger ans = BigInteger.ZERO;
		if (!str.startsWith("+") && !str.startsWith("-")) {
			while (str.charAt(i) != '+' && str.charAt(i) != '-') {
				i++;
			}
			ans = ans.add(new BigInteger(str.substring(0, i)));
		}
		while (i < str.length()) {
			if (str.charAt(i) == '+') {
				Object[] res;
				if (str.charAt(i + 1) == '(') {
					res = bracket(str, i);
				} else {
					res = chain(str, i, '+');
				}
				ans = ans.add((BigInteger) res[0]);
				i = (int) res[1];
			} else {
				Object[] res;
				if (str.charAt(i + 1) == '(') {
					res = bracket(str, i);
				} else {
					res = chain(str, i, '-');
				}
				ans = ans.add(((BigInteger) res[0]).negate());
				i = (int) res[1];
			}
		}
		System.out.println(ans);
	}

	private static Object[] bracket(String str, int i) {
		int j = i + 2;
		while (str.charAt(j) != ')') {
			j++;
		}
		BigInteger a = new BigInteger(str.substring(i + 2, j));
		i = ++j;
		try {
			while (str.charAt(j) != '+' && str.charAt(j) != '-') {
				j++;
			}
		} catch (StringIndexOutOfBoundsException ignored) {
		}
		BigInteger b = new BigInteger(str.substring(i, j));
		return new Object[]{a.multiply(b), j};
	}

	private static Object[] chain(String str, int i, char op) {
		int j = i;
		while (str.charAt(j) == op) {
			j++;
		}
		BigInteger a = new BigInteger((j - i) + "");
		i = j;
		try {
			while (str.charAt(j) != '+' && str.charAt(j) != '-') {
				j++;
			}
		} catch (StringIndexOutOfBoundsException ignored) {
		}
		BigInteger b = new BigInteger(str.substring(i, j));
		return new Object[]{a.multiply(b), j};
	}

}
```

---

## 作者：灼眼的夏娜 (赞：3)

这题就TMD一毒瘤，调了我整整一天QWQ

~~然而机房里的其他dalao居然一个小时就过了~~

我看了下别人的代码，具体有两种写法：重载 / 模拟

开始我用的是模拟，然而发现它极其容易写挂，因此在敲了三个小时后我放

弃了模拟，转向写重载

流程如下：

①发现运算只涉及到“+，-，*”三种，因此我们只需要重载三个运算符

②涉及到正与负的转换，我们只要在重载的过程中判断一下即可

③可以将输出也进行重载，方便debug

然而就这样我还是调了一整天，以至于让我以后再也不想碰高精了

最后双手捧上蒟蒻的代码，以表示庆祝我过了这道毒瘤题

## code
```cpp
#include<bits/stdc++.h>
#define R register

using namespace std;
char ch[2005];
int cnt;

struct BIG {
	int len;
	bool flag;
	int v[10005];
	BIG() { memset(v,0,sizeof(v)),len = 0,flag = 1; }
	int& operator [] (int x) { return v[x]; }
}ans;

BIG operator + (BIG A,BIG B);
BIG operator - (BIG A,BIG B);
ostream& operator << (ostream &out,const BIG &a);

BIG Fabs(BIG A) {A.flag = false; return A;}

bool operator < (BIG a,BIG b) {
    if(a.flag && !b.flag) return false;
   	if(b.flag && !a.flag) return true;
   	if(!a.flag && !b.flag) { a.flag = b.flag = true;return b < a; }
   	if(a.len < b.len) return true;
   	if(a.len > b.len) return false;
   	for(int i = a.len;i >= 1;-- i) {
       	if(a.v[i] < b.v[i]) return true;
       	if(a.v[i] > b.v[i]) return false;
   	}
    return false;
}

BIG operator + (BIG A,BIG B) {
	if(!A.flag && !B.flag) {
		A.flag = B.flag = 1;
		return Fabs(A + B);
	}
	if(!A.flag && B.flag) { A.flag = 1;return B - A; }
	if(A.flag && !B.flag) { B.flag = 1;return A - B; }
	BIG C;
	C.len = max(A.len,B.len);
	for(R int i = 1;i <= C.len;++ i) {
		C[i] += A[i] + B[i];
		if(C[i] >= 10) {
			C[i + 1] += C[i] / 10;
			C[i] %= 10;
		}
	}
	while(C[C.len] > 0) ++ C.len;-- C.len;
	return C;
}

BIG operator - (BIG A,BIG B) {
	BIG C;
	if(A.flag && !B.flag) { B.flag = true; return A + B; }
    if(B.flag && !A.flag) { A.flag = true; return Fabs(A + B);}
    if(!A.flag && !B.flag) { B.flag = true; return A + B;}
    if(A < B) C.flag = false,swap(A, B);
    C.len = A.len;
    for(int i = 1; i <= C.len; ++i) C[i] = A[i];
    for(int i = 1; i <= B.len; ++i) {
        C[i] -= B[i];
        while(C[i] < 0) C[i] += 10,--C[i + 1];
    }
    for(int i = 1; i <= C.len; ++i) while(C[i] < 0) C[i] += 10,-- C[i + 1];
    while(C[C.len] == 0 && C.len) -- C.len;
    return C;
}

BIG operator * (BIG A,BIG B) {
	BIG C;
	C.len = A.len + B.len - 1;
	for(int i = 1; i <= A.len; ++i)
		for(int j = 1; j <= B.len; ++j)
			C[i + j - 1] += A[i] * B[j], C[i + j] += C[i + j - 1] / 10, C[i + j - 1] %= 10;
	while(C[C.len + 1]) ++C.len;
	C.flag = (A.flag == B.flag);
	return C;
}

inline BIG read(int &i){
	BIG a;
	while(ch[i] > '9' || ch[i] < '0') ++ i;
	while(ch[i] <= '9' && ch[i] >= '0') a[++a.len] = ch[i] ^ 48,++ i;
	for(int j = 1;j <= (a.len >> 1);++ j) swap(a[j],a[a.len - j + 1]);
	return a;
}

ostream& operator << (ostream &out,const BIG &a)
{
	if(!a.len) {
		cout<<"0";
		return out;
	}
	if(!a.flag) cout<<"-";
	for(R int i = a.len;i >= 1;-- i) printf("%d",a.v[i]);
	return out;
}

inline BIG split(int x) {
	BIG A;
	while(x) A[++A.len] = x % 10,x /= 10;
	return A;
}

int main() {
    scanf("%s",ch + 1); 
    int len = strlen(ch + 1);
    for(int i = 1; i <= len;) {
//	大力讨论可能出现的情况
        if(ch[i] == '+' && ch[i + 1] == '(') {
            BIG k = read(i);    
            BIG o = read(i);
            ans = ans + k * o;
        }
        
	if(ch[i] == '-' && ch[i + 1] == '(') {
            BIG k = read(i);
            BIG o = read(i);
            ans = ans - k * o;
        }
        
	if(ch[i] == '+' && ch[i + 1] == '+') {
            cnt = 0;
            while(ch[i] == '+') ++i, ++cnt;
            BIG k = split(cnt);
            BIG o = read(i);
            ans = ans + k * o;
        }
        
	if(ch[i] == '-' && ch[i + 1] == '-') {
            cnt = 0;
            while(ch[i] == '-') ++i, ++cnt;
            BIG k = split(cnt);
            BIG o = read(i);
            ans = ans - k * o;
        }
        
	if(ch[i] == '+' && ch[i + 1] >= '0' && ch[i + 1] <= '9') ans = ans + read(i);
        
	if(ch[i] == '-' && ch[i + 1] >= '0' && ch[i + 1] <= '9') ans = ans - read(i);
//	注意开始要先把它加进去
        if(i == 1 && ch[i] >= '0' && ch[i] <= '9') ans = read(i);
    }
    cout<<ans;
    return 0;
}
```

完结撒~~花~~（泪）


---

## 作者：帝千秋丶梦尘 (赞：2)

呃。。。。第一次(~~水~~)发一篇题解，好激动QwQ

言归正传，这是我第一道切掉的紫题

[没看过的看看题先（肯定有做题先点题解的）](https://www.luogu.com.cn/problem/P1557)

这道题目集合了我这种蒟蒻最不愿意碰到的字符串与高精度结合之题，本来还以为

就是普通的字符串的判断（看你细不细心），然后随手一点开讨论。。。。

要带高精度！！！！！

然后为了切一道紫题，我整整花了2小时调高精度QAQ

好好好，终于言归正传

首先其实题目还是很好理解的：就是一头奶牛闲着无聊随便玩玩，然后就开发出了一种新的算式（~~我没觉得有多新~~）

# 注意事项：

括号里的算式就用乘号（不要像我一样懒得打高精乘），然后就是先统计下加减符号数量。最后其实写过高精的都知道一般算式（或数字）都要以字符串的形式输入的，不会的建议先切一下模板题

题目其实也不难，有足够耐心去调题就能过（一遍过的当我没说）

~~详细~~注释都在代码里了，望管理大大能够给过（不对或多余之处(多余好多)还望大佬们提意见，求勿喷QwQ）

```
#include<bits/stdc++.h>//习惯性万能头（不是个好习惯）
using namespace std;
int flag,num[50001],ans[50001],ans2[50001],lans2,lans,lnum,lcs;
int len=-1,tmp=-1,cs[5001],flag2,flag3,a[50001],b[50001],c[50001];
int x,lena,lenb,lenc;//大佬们凑合着康康
char s[50001],ss[50001];//输入的算式
inline void add()//加法1（要加的数）
{
	int k=0,x=0;
	while(k<=lans||k<=lnum)
	{
		ans[k]=ans[k]+num[lnum-k]+x;
		x=ans[k]/10;
		ans[k]%=10;
		k++;
	}
	if(x==1)
	{
		ans[k]=1;
		k++;
	}
	lans=k-1;
	return ;
}
inline void addd()//加法2（要减的数）
{
	int k=0,x=0;
	while(k<=lans2||k<=lnum)
	{
		ans2[k]=ans2[k]+num[lnum-k]+x;
		x=ans2[k]/10;
		ans2[k]%=10;
		k++;
	}
	if(x==1)
	{
		ans2[k]=1;
		k++;
	}
	lans2=k-1;
	return ;
}
inline void jian()//减法（将要加的数和要减的数相减（谁大谁为被减数））
{
	int k=0;
	if(!flag3)
	{ 
		while(k<=lans||k<=lans2)
		{
			if(ans[k]<ans2[k])
			{
				ans[k]+=10;
				ans[k+1]--;
			}
			ans[k]=ans[k]-ans2[k];
			k++;
		}
	} 
	else if(flag3)
	{
		while(k<=lans||k<=lans2) 
		{
			if(ans2[k]<ans[k])
			{
				ans2[k]+=10;
				ans2[k+1]--;
			}
			ans2[k]=ans2[k]-ans[k];
			k++;
		}
	}
	if(flag3)
		lans2=k-1;
	else if(!flag3)
		lans=k-1;
	return ;
}
inline void chenfa()//这总看得出来吧（普通乘法）
{
	lena=lnum+1,lenb=lcs+1; 
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	for(register int i(lnum),j(1);i>=0;--i,++j)
	{
		a[j]=num[i];
	}
	if(!flag2)
	{
		for(register int i(0),j(1);i<=lcs;++i,++j)
		{
			b[j]=cs[i];
		}
	}
	else if(flag2)
	{
		for(register int i(lcs),j(1);i>=0;--i,++j)
		{
			b[j]=cs[i];
		}
	}
	for(register int i(1);i<=lena;++i)
	{
		x=0;
		for(register int j(1);j<=lenb;++j)
		{
			c[i+j-1]+=a[i]*b[j]+x;
			x=c[i+j-1]/10;
			c[i+j-1]%=10;
		}
		c[i+lenb]=x;
	}
	lenc=lena+lenb;
	while(c[lenc]==0&&lenc>1)
		lenc--;
	for(register int i(lenc),j(0);i>=1;--i,++j)
	{
		num[j]=c[i];
	}
	lnum=lenc-1;
	return ;
}
inline bool pd()//判断要加的数大还是要减的数大
{
	for(register int i(lans);i>=0;--i)
	{
		if(ans[i]>ans2[i])
		{
			return false;
		}
		else if(ans[i]<ans2[i])
		{
			return true;
		}
	}
	return false;
}
int main(void)//听说加void能变快（雾
{
	cin>>ss;//以字符串形式输入
	memset(cs,0,sizeof(cs));
	memset(num,0,sizeof(num));
	memset(ans,0,sizeof(ans));//清空数组
	int lens=strlen(ss);//string类型用.length()
	if(ss[0]>='0'&&ss[0]<='9')
	{
		s[0]='+';
		for(register int i(0);i<lens;++i)
		{
			s[i+1]=ss[i];
		}
		lens++;
	}//如果开头是数字就先加个“+”号（我是这么写的
	else
	{
		for(register int i(0);i<lens;++i)
		{
			s[i]=ss[i];
		}
	}//调动字符串位置(好像不需要
	s[lens]='+';
	if(s[1]!='(')
	{
		cs[0]=1;
	}
	for(register int o(0);o<=lens;++o)
	{
		if(s[o]>='0'&&s[o]<='9')
		{
			if(flag!=0)
			{
				cs[lcs++]=s[o]-'0';
			}
			else
			{
				num[lnum++]=s[o]-'0';
			}
		}
		else if(s[o]==')')
		{
			flag=0;
		}
		else if(s[o]=='+')
		{
			if(s[o-1]=='+')
			{
				cs[0]++;
				for(register int i(0);i<lcs;++i)
				{
					if(cs[i]>=10)
					{
						cs[i]-=10;
						cs[i+1]++;
					}
				}
				if(cs[lcs]>=10)
				{
					cs[lcs]=0;
					lcs++;
					cs[lcs]=1; 
				}
			}
			if(o>=1&&s[o-1]!='+'&&(tmp==1||tmp==-1))
			{
				if(flag2==1)
				{
					lcs--;
				}
				lnum--;
				chenfa();
				if(tmp==1)
				{
					add();
					while(ans[lans]==0&&lans>0)
					lans--;
				}
				else if(tmp==-1)
				{
					addd();
					while(ans2[lans2]==0&&lans2>0)
						lans2--;
				} 
				memset(num,0,sizeof(num));
				memset(cs,0,sizeof(cs));
				lcs=0,flag=0,lnum=0,flag2=0;
				cs[lcs]=1;
			}
			if(s[o+1]=='(')
			{
				flag=1;
				flag2=1;
				cs[0]=0;
			}
			tmp=1;
		}
		else if(s[o]=='-')
		{
			if(s[o-1]=='-')
			{
				cs[0]++;
				for(register int i(0);i<lcs;++i)
				{
					if(cs[i]>=10)
					{
						cs[i]-=10;
						cs[i+1]++;
					}
				}
				if(cs[lcs]>=10)
				{
					cs[lcs]=0;
					lcs++;
					cs[lcs]=1;
				}
			}
			if(o>=1&&s[o-1]!='-'&&(tmp==1||tmp==-1))
			{
				if(flag2==1)
				{
					lcs--;
				}
				lnum--;
				chenfa();
				if(tmp==1)
				{
					add();
					while(ans[lans]==0&&lans>0)
					lans--;
				}//把要加的数字弄到一起
				else if(tmp==-1)
				{
					addd();
					while(ans2[lans2]==0&&lans2>0)
						lans2--;
				}//把要减的数字弄到一起
				memset(num,0,sizeof(num));
				memset(cs,0,sizeof(cs));
				lcs=0,flag=0,lnum=0,flag2=0;
				cs[lcs]=1;
			}
			if(s[o+1]=='(')
			{
				flag=1;
				flag2=1;
				cs[0]=0;
			}
			tmp=-1;
		}
	}//其实中间都有好多不需要的步骤（毕竟好久前写的了），的确不够简洁，希望你们不要犯我这种情况哦。
	if(lans<lans2)
	{
		flag3=1;
		printf("-");
	}//判断是否最后答案为负数。
	else if(lans==lans2)
	{
		if(pd()==true)
		{
			flag3=1;
			printf("-");
		}
	}//同上
	jian();//减一下该加起来的部分和该减掉的部分。
	if(!flag3)
	{
		while(ans[lans]==0&&lans>0)
			lans--;//去掉多余的0
		for(register int i(lans);i>=0;--i)
		{
			printf("%d",ans[i]);
		}//反向输出，基本操作
		return 0;
	}
	else if(flag3)
	{
		while(ans2[lans2]==0&&lans2>0)
			lans2--;//同上
		for(register int i(lans2);i>=0;--i)
		{
			printf("%d",ans2[i]);
		}//若是负数也一样输出
		return 0;
	}
	return 0;//一个好习惯QwQ
}
```
## 各位看官走好，( ^_^ )/~~拜拜

---

## 作者：Leianha (赞：2)

## 高精&模拟

提供一种不一样的高精度写法。

我们可以使用结构体来模拟高精度，顺便重载一下$+$ $-$ $\times$就可以啦。但是我们很快就会发现一些问题，如果正数减负数怎么办？~~用Pascal~~当然是大力讨论啦。

我们可以先不管数的正负，在进行加减的时候只处理 正数加正数 和 大的整数减小的正数，如果有负数就变号再进行加减法。乘法的话遵循同号为正数异号为负就可以啦。另外重载<<就可以输出结构体，用起来十分的方便。以下提供的写法可以当做模板食用。

这个题还有十分麻烦的模拟，我们使用一个类似快读的函数就能读入啦。另外大力讨论一下7种情况，注意一下它的第一个数前面可能没有加号，需要处理一下防止读不进去数。

还有很重点的一项就是当答案是0的时候，它的len也是0，所以需要特判一下。其他的需要注意的地方都在代码的注释里，请放心食用。

最后献上我~~丑陋~~的代码。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n;
char a[5100];
struct gj
{
	int len,zheng;//len：长度 zheng：正负标记0为负1为正 
	int v[10000];
	gj(){len=0;memset(v,0,sizeof(v));zheng=1;}
	gj(int x)
	{
		if(x>=0)zheng=1;
		else x=-x,zheng=0;
		len=0;memset(v,0,sizeof(v));
		while(x)
		{
			v[++len]=x%10;
			x/=10;
		}
	}
	friend bool operator <(const gj &a,const gj &b)
	{
	    if(a.len<b.len)return 1;
	    if(a.len>b.len)return 0;
	    for(int i=a.len;i>=1;--i)
	    {
	    	if(a.v[i]<b.v[i])return 1;
	    	if(a.v[i]>b.v[i])return 0;
	    }
	    return 0;
	}
}ans;
/*------以下为重载部分------*/ 
ostream& operator << (ostream &out,const gj &a);
gj operator -(gj a,gj b);
gj operator +(gj a,gj b);

gj operator +(gj a,gj b)
{
	if(!a.zheng&&!b.zheng)
	{
		a.zheng=b.zheng=1;
		gj c=a+b;
		c.zheng=0;
		return c;
	}
	if(!a.zheng&&b.zheng)
	{
		a.zheng=b.zheng=1;
		return b-a;
	}
	if(a.zheng&&!b.zheng)
	{
		a.zheng=b.zheng=1;
		return a-b;
	}
	int len=a.len+b.len;
	gj c;
	c.len=len;
	for(int i=1;i<=len;++i)c.v[i]=a.v[i]+b.v[i];
	for(int i=1;i<=len;++i)
	{
		if(c.v[i]>=10)
		{
			++c.v[i+1];
			c.v[i]-=10;
		}
	}
	while(c.len&&!c.v[c.len])c.len--;
	return c;
}
gj operator -(gj a,gj b)
{
	if(!a.zheng&&!b.zheng)
	{
		a.zheng=b.zheng=1;
		return b-a;
	}
	if(!a.zheng&&b.zheng)
	{
		a.zheng=1;
		gj c=a+b;
		c.zheng=0;
		return c;
	}
	if(a.zheng&&!b.zheng)
	{
		b.zheng=1;
		gj c=a+b;
		return c;
	}
	if(a.zheng&&b.zheng&&a<b)
	{
		gj c=b-a;
		c.zheng=0;
		return c;
	}
	int len=max(a.len,b.len);
	gj c;
	for(int i=1;i<=len;++i)c.v[i]=a.v[i]-b.v[i];
	c.len=len;
	for(int i=1;i<=c.len;++i)
	{
		if(c.v[i]<0)
		{
			c.v[i+1]--;
			c.v[i]+=10;
		}
	}
	while(c.len&&!c.v[c.len])c.len--;
	return c;
}
gj operator *(gj a,gj b)
{
	gj c;
	for(int i=1;i<=a.len;++i)
	for(int j=1;j<=b.len;++j)
	c.v[i+j-1]+=a.v[i]*b.v[j];
	c.len=a.len+b.len;
	for(int i=1;i<=c.len-1;++i)
	{
		if(c.v[i]>=10)
		{
			c.v[i+1]+=c.v[i]/10;
			c.v[i]%=10;
		}
	}
	while(c.v[c.len]==0&&c.len>1)--c.len;
	if(a.zheng!=b.zheng)c.zheng=0;
	else c.zheng=1;
	return c;
}
ostream& operator << (ostream &out,const gj &a)//方便使用cout 
{
	if(!a.len)//一定要注意答案是0得情况 
	{
		cout<<"0";
		return out;
	}
	if(!a.zheng)cout<<"-";
	for(int i=a.len;i>=1;i--)printf("%d",a.v[i]);
	return out;
}
/*------以上为重载部分------*/ 
gj read(int pos)//类似快读 
{
	gj s;
	while(a[pos]<'0'||a[pos]>'9')pos++;
	while(a[pos]>='0'&&a[pos]<='9')s.v[++s.len]=a[pos]-'0',pos++;
	for(int i=1;i<=s.len/2;++i)swap(s.v[i],s.v[s.len-i+1]);//因为是正着读的所以要反过来 
	s.zheng=1;
	return s;
}
int main()
{
	scanf("%s",a+1);n=strlen(a+1);
	ans.zheng=1;
	for(int i=1;i<=n;++i)
	{
		if(a[i]=='+'&&a[i+1]=='(')//加某个数*某个数 
		{
			gj k=read(i+2);
			while(a[i]<'0'||a[i]>'9')i++;
			while(a[i]>='0'&&a[i]<='9')i++;
			i++;
			ans=ans+read(i)*k;
		}
		else if(a[i]=='-'&&a[i+1]=='(')//减某个数 *某个数
		{
			gj k=read(i+2);
			while(a[i]<'0'||a[i]>'9')i++;
			while(a[i]>='0'&&a[i]<='9')i++;
			i++;
			ans=ans-read(i)*k;
		}
		else if(a[i]=='+'&&a[i+1]=='+')//连加 
		{
			int cnt=0;
			while(a[i]=='+')cnt++,i++;
			ans=ans+read(i)*gj(cnt);
		}
		else if(a[i]=='-'&&a[i+1]=='-')//连减 
		{
			int cnt=0;
			while(a[i]=='-')cnt++,i++;
			ans=ans-read(i)*gj(cnt);
		}
		else if(a[i]=='+'&&a[i+1]>='0'&&a[i+1]<='9')ans=ans+read(i+1);//加某个数 
		else if(a[i]=='-'&&a[i+1]>='0'&&a[i+1]<='9')ans=ans-read(i+1);//减某个数 
		else if(i==1&&a[i]>='0'&&a[i]<='9')ans=read(i);//读入第一个数 
	}
	cout<<ans;
	return 0;
}
/*
+(8)9-(10)9+++6
*/
```


---

## 作者：JJA_ (赞：1)

## 思路：

获取整行的字符串（一个算式），再一位一位处理，积攒加法或减法的次数，之后一起累加。

### 分块代码：

需要用到的变量：

```cpp
big pl,su;//加的次数。
big sum=0;//总和
bool aos=1;//判断现在是加法还是减法，第一位可能没有运算符，默认是加法。
stringstream ss;//字符串流，后面将用到。
```

首先，需要获取一个字符串，再分位获取：

```cpp
int check(int i){//判断处理函数。
	if(str[i]=='+'){
		return 1;
	}
	else if(str[i]=='-'){
		return 2;
	}
	else if(str[i]=='('){
		return 3;
	}
	else if(str[i]==')'){
		return 5;
	}
	else if(str[i]>='0'&&str[i]<='9'){
		return 4;
	}
}
```

```cpp
for(int i=0;i<str.size();i++){
	ss.clear();
	switch(check(i)){
		//do sth.
	}
}
```

之后，分别处理各类运算符的情况：

```cpp
case 1:{//如果是加号
	pl++;
	aos=1;
	break;
}
```

```cpp
case 2:{//减号
	su++;
	aos=0;
	break;
}
```

如果是括号，要稍微处理一下，这里用了字符串流，统计括号后的数字位数，再将这些数字用字符串流流入整型数字。

```cpp
case 3:{
	int n;
	int j=i+1,aaa=0;//aaa是记录数字的位数。
	while(check(j)==4){
		j++,aaa++;
	}
	j--;
	for(int p=i+1;p<=j;p++){
		ss<<str[p];
	}
	ss>>n;
	ss.clear();//清除字符串流缓存区。
	if(su!=0){
		su=n;
	}
	else{
		pl=n;
	}
	i+=aaa;//避免重复处理数字。
	break;
}
```

```cpp
case 5{
	break;//右括号，执行了个寂寞
}
```

```cpp
case 4:{//如果是数字，但是没有左括号，那就说明是加或减的数字。
	int n;
	int j=i+1;
	while(check(j)==4){
		j++;
	}
	j--;
	for(int p=i;p<=j;p++){
		ss<<str[p];
	}
	ss>>n;
	ss.clear();
	kr(n);//题目所给的运算。
	break;
}
```

之后是完成题意的计算，很简单，就是乘一下。

```cpp
void add(int n){//加法
	sum+=n*pl;
	pl=0;
}
void sub(int n){//减法
	sum-=n*su;
	su=0;
}
void kr(int n){//奇怪的运算
	if(aos==1){//加法
		add(n);
	}
	else if(aos==0){//减法
		sub(n);
	}
}
```

于是将上面的代码交上去，发现只有 $40pts$ 。

为什么呢？

![image.png](https://i.loli.net/2020/12/27/mlRIL3V1Fry6oQA.png)

~~转型py我觉得是来不及了。~~

那就拿出私藏已久的高精模板吧。

[Link](https://www.luogu.com.cn/paste/0aux9w45)

在将 `sum,pl,su,n` 都换成高精后，有一个问题：字符串不能流入高精。
所以，只能一位一位处理流入。

```cpp
big n=0;
int inn;
for(int p=i;p<=j;p++){
	ss<<str[p];
	ss>>inn;
	ss.clear();
	n+=inn;
	n*=10;
}
```
但是这里n好像多乘以一个 $10$ ，所以之后记得除掉。

但是，交上去后，仍然只有 $90pts$ ，why？

随便测试一组数据：
`-----2+++++3`
发现输出为 `-5` 。

所以，多了一组特判：
```cpp
bool flag=0;
int check(int i){//修改后的判断函数
	if(i==0&&str[i]=='-'){
		flag=1;
	}
	if(str[i]=='+'){
		return 1;
	}
	else if(str[i]=='-'){
		return 2;
	}
	else if(str[i]=='('){
		return 3;
	}
	else if(str[i]==')'){
		return 5;
	}
	else if(str[i]>='0'&&str[i]<='9'){
		return 4;
	}
}

void add(big n){//修改后的加法函数
	big summ=0;
	summ+=n*pl;
	if(flag==1){
		if(abs(sum)<abs(summ)&&sum+summ<0){
			sum+=summ;
			sum=abs(sum);
			flag=0;
		}
		else sum+=summ;	
	}
	else
	sum+=summ;
	pl=0;
}
```
这样就愉快地AC了。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 200005
const int _N=1e6+7,_B=1e9;
char _S[_N];
ll _C[_N*2/9];
struct big{
    vector<int>a;
    bool f;
    big(){a.clear(),f=0;}
    big(const char*s){
        int i=0,l=strlen(s),j;
        if(a.clear(),f=0,s[0]=='-')i=f=1;
        if(s[i]=='0')return;
        j=(l-i-1)%9+1,a.push_back(0);
        for(;i<l;(a.back()*=10)+=s[i++]-48,--j)if(!j)a.push_back(0),j=9;
        reverse(a.begin(),a.end());
    }
    big(const string&s){*this=s.c_str();}
    big(int x){
        a.clear(),x<0?(x=-x,f=1):(f=0);
        if(x)x<_B?(a.push_back(x)):(a.push_back(x%_B),a.push_back(x/_B));
    }
    big(const ll&x){sprintf(_S,"%lld",x),*this=_S;}
    explicit operator int(){
        int l=a.size(),i,r=0;
        for(i=l-1;~i;--i)r=r*_B+a[i];
        return f?-r:r;
    }
    explicit operator ll(){
        int l=a.size(),i;
        ll r=0;
        for(i=l-1;~i;--i)r=r*_B+a[i];
        return f?-r:r;
    }
    explicit operator bool(){return!a.empty();}
    int abscmp(const big&x)const{
        int l=a.size(),o=x.a.size();
        if(l!=o)return l<o?-1:1;
        while(l--)if(a[l]!=x.a[l])return a[l]<x.a[l]?-1:1;
        return 0;
    }
    int cmp(const big&x)const{
        if(a.empty())return x.a.empty()?0:(x.f?1:-1);
        if(x.a.empty())return f?-1:1;
        if(!f&&x.f)return 1;
        if(f&&!x.f)return -1;
        return f?-abscmp(x):abscmp(x);
    }
    friend bool operator<(const big&x,const big&y){return x.cmp(y)<0;}
    friend bool operator>(const big&x,const big&y){return x.cmp(y)>0;}
    friend bool operator<=(const big&x,const big&y){return x.cmp(y)<=0;}
    friend bool operator>=(const big&x,const big&y){return x.cmp(y)>=0;}
    friend bool operator==(const big&x,const big&y){return x.cmp(y)==0;}
    friend bool operator!=(const big&x,const big&y){return x.cmp(y)!=0;}
    big&operator+(){return*this;}
    big operator-(){
        big x=*this;
        return x.f^=1,x;
    }
    void add1(){
        if(++a[0]==_B){
            a.push_back(0);
            for(int i=0;a[i]==_B;++i)a[i]=0,++a[i+1];
            if(!a.back())a.pop_back();
        }
    }
    void sub1(){
        if(--a[0]==-1){
            for(int i=0;a[i]==-1;++i)a[i]+=_B,--a[i+1];
            if(!a.back())a.pop_back();
        }
    }
    big&operator++(){return a.empty()?(a.push_back(1),f=0,void()):(f?sub1():add1()),*this;}
    big&operator--(){return a.empty()?(a.push_back(1),f=1,void()):(f?add1():sub1()),*this;}
    big operator++(int){
        big x=*this;
        return a.empty()?(a.push_back(1),f=0,void()):(f?sub1():add1()),x;
    }
    big operator--(int){
        big x=*this;
        return a.empty()?(a.push_back(1),f=1,void()):(f?add1():sub1()),x;
    }
    void fit(){while(!a.empty()&&!a.back())a.pop_back();}
    void add(const big&x){
        int i,l=a.size(),o=x.a.size(),j;
        if(l<o)a.resize(o);
        a.push_back(0);
        for(i=0;i<o;++i){
            j=a[i]+x.a[i];
            if(j>=_B)j-=_B,++a[i+1];
            a[i]=j;
        }
        fit();
    }
    void sub(const big&x){
        int i,l=a.size(),o=x.a.size(),j;
        for(i=0;i<o;++i){
            j=a[i]-x.a[i];
            if(j<0)j+=_B,--a[i+1];
            a[i]=j;
        }
        for(i=o;i<l;++i)if(a[i]<0)a[i]+=_B,--a[i+1];
        fit();
    }
    void mul(const big&x){
        int i,l=a.size(),o=x.a.size(),j,k;
        ll w;
        for(memset(_C,0,(k=l+o)*8),i=0;i<o;++i)for(j=0;j<l;++j)
        w=x.a[i]*1ll*a[j]+_C[i+j],_C[i+j]=w%_B,_C[i+j+1]+=w/_B;
        for(a.resize(k),i=0;i<k;++i)a[i]=_C[i];
        fit();
    }
    int div(const int&x){
        int i,l=a.size();
        ll w=0;
        for(i=l-1;~i;--i)w=w*_B+a[i],a[i]=w/x,w-=a[i]*1ll*x;
        return fit(),w;
    }
    big div(const big&x){
        int i,l=a.size(),o=x.a.size(),j=l-o;
        ll u,v,w;
        big r;
        if(j<0)return r=*this,*this=0,r;
        for(i=l-1;i>j;--i)r=r*_B+a[i];
        for(i=j,a.resize(j+1);~i;--i){
            r=r*_B+a[i],u=0,v=_B-1;
            while(u<=v){
                w=u+v>>1;
                if(x*w<=r)u=w+1;else v=w-1;
            }
            a[i]=u-1,r-=x*a[i];
        }
        return fit(),r;
    }
    big&operator+=(const big&x){
        if(f==x.f)add(x);
        else if(abscmp(x)>=0)sub(x);
        else{
            big y=x;
            y.sub(*this),*this=y,f^=1;
        }
        return*this;
    }
    big&operator-=(const big&x){
        if(f!=x.f)add(x);
        else if(abscmp(x)>=0)sub(x);
        else{
            big y=x;
            y.sub(*this),*this=y,f^=1;
        }
        return*this;
    }
    big&operator*=(const big&x){return mul(x),f=(f==x.f?0:1),*this;}
    big&operator/=(const int&x){return div(abs(x)),f=(((f&&x<0)||(!f&&x>0))?0:1),*this;}
    big&operator/=(const big&x){return div(x),f=(f==x.f?0:1),*this;}
    big&operator/=(const ll&x){return*this/=(big)x;}
    big&operator%=(const int&x){return*this=f?-div(abs(x)):div(abs(x));}
    big&operator%=(const big&x){return*this=f?-div(x):div(x);}
    big&operator%=(const ll&x){return*this%=(big)x;}
    friend big operator+(big x,const big&y){return x+=y,x;}
    friend big operator-(big x,const big&y){return x-=y,x;}
    friend big operator*(big x,const big&y){return x*=y,x;}
    friend big operator/(big x,const ll&y){return x/=y,x;}
    friend big operator/(big x,const int&y){return x/=y,x;}
    friend big operator/(big x,const big&y){return x/=y,x;}
    friend ll operator%(big x,const ll&y){return x%=y,(ll)x;}
    friend int operator%(big x,const int&y){return x%=y,(int)x;}
    friend big operator%(big x,const big&y){return x%=y,x;}
};
void in(big&x){scanf("%s",_S),x=_S;}
void out(const big&x){
    int i=x.a.size();
    if(!i)return putchar('0'),void();
    if(x.f)putchar('-');
    for(printf("%d",x.a[--i]);i--;)printf("%09d",x.a[i]);
}
void out(const big&x,const char&c){out(x),putchar(c);}
void swap(big&x,big&y){swap(x.f,y.f),swap(x.a,y.a);}
big abs(big x){return x.f=0,x;}
inline big pow(big a,int b){
    big r=1;
    for(;b;b>>=1){
        if(b&1)r*=a;
        if(b)a*=a;
    }
    return r;
}
big gcd(big a,big b){
    big r=1;
    while(1){
        if(!a||!b)return(a+b)*r;
        while(a.a[0]%2==0&&b.a[0]%2==0)r*=2,a/=2,b/=2;
        while(a.a[0]%2==0)a/=2;
        while(b.a[0]%2==0)b/=2;
        if(a<b)swap(a,b);
        a-=b;
    }
}
big pl,su;
big sum=0;
bool aos=1;
bool flag=0;
void add(big n){
	big summ=0;
	summ+=n*pl;
	if(flag==1){
		if(abs(sum)<abs(summ)&&sum+summ<0){
			sum+=summ;
			sum=abs(sum);
			flag=0;
		}
		else sum+=summ;	
	}
	else
	sum+=summ;
	pl=0;
}
void sub(big n){
	sum-=n*su;
	su=0;
}
void kr(big n){
	if(aos==1){
		add(n);
	}
	else if(aos==0){
		sub(n);
	}
}
string str;
int check(int i){
	if(i==0&&str[i]=='-'){
		flag=1;
	}
	if(str[i]=='+'){
		return 1;
	}
	else if(str[i]=='-'){
		return 2;
	}
	else if(str[i]=='('){
		return 3;
	}
	else if(str[i]==')'){
		return 5;
	}
	else if(str[i]>='0'&&str[i]<='9'){
		return 4;
	}
}
void solve1(string str){
	stringstream ss;
    for(int i=0;i<str.size();i++){
    	ss.clear();
		switch(check(i)){
    		case 1:{
    			pl++;
    			aos=1;
				break;
			}
			case 2:{
				su++;
				aos=0;
				break;
			}
			case 3:{
				big n=0;
				int nn;
				int j=i+1,aaa=0;
				while(check(j)==4){
					j++,aaa++;
				}
				j--;
				for(int p=i+1;p<=j;p++){
					ss<<str[p];
					ss>>nn;
					ss.clear();
					n+=nn;
					n*=10;
				}
				n/=10; 
				if(su!=0){
					su=n;
				}
				else{
					pl=n;
				}
				i+=aaa;
				break;
			}
			case 5:{
				break;
			}
			case 4:{
				big n=0;
				int inn;
				int j=i+1;
				while(check(j)==4){
					j++;
				}
				j--;
				for(int p=i;p<=j;p++){
					ss<<str[p];
					ss>>inn;
					ss.clear();
					n+=inn;
					n*=10;
				}
				kr(n);
				break;
			}
		}
	}
	out(sum/10);
}
int main(){
	getline(cin,str);
	solve1(str);
}
```

---

## 作者：编程客 (赞：1)

### 先说一下自己的经历：
- 遇到这道题时是在打模拟赛时，当时只处理了算式，没有想到高精度（也是时间不够），只有六十分。打完比赛，磕了好久的高精度，终于AC了这道题。

# 本篇题解主要提供思路

- 我的代码是用字符串高精度写的，大佬可以用压位或int数组来存的方法。

- 本题难点主要在运算式处理和高精度 ~~等于没说~~
#### 首先是加减法
- 当只有一个加法或减法是自然是按正常思路去做，但如果有多个符号时我们就需要用一个变量来存储符号数量，还需要存储是连续加法还是减法。处理方法：
```cpp
if(str[i]=='+')
{
	flag="1";
	if(i!=0&&str[i-1]=='+')
	{
		t++;
	}
}
if(str[i]=='-')
{
	flag="-1";
	if(i!=0&&str[i-1]=='-')
	{
		t++;
	}
}
```
#### 接着是乘法
- 而遇到括号时，需要把括号内的数读入，再把括号后面的数也读入，直接相乘即可。

## 最重要的高精度
- 正常的奆佬们应该都会，重点是负数。

#### 加法：

- 先按绝对值按a大 b小排下序；

- 如果a负b正 则是-（a的绝对值-b）；

- 如果a正b负 则是a-(b的绝对值)；

- 如果同号，则绝对值相加，符号取相同的符号

#### 减法：

- 主要是加法，减法只用普通的非负型减法就行了

#### 乘法：

- 同号得正，异号得负

### 再次声明一下，此篇题解主要提供思路，因为我的代码不是很好懂。

最后附上代码：
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
string str;
string dr(long long &i)
{
	string t="";
	while(str[i]>='0'&&str[i]<='9')
	{
		t+=str[i];
		i++;
	}
	i--;
	return t;
}
void diao(string &a)
{
    for(int i=0;i<a.size()/2;i++)
    {
        swap(a[i],a[a.size()-i-1]);
    }
}
string zero(int n)
{
    string s="";
    for(int i=1;i<=n;i++)
    {
        s+="0";
    }
    return s;
}
string jian(string a,string b) //高精度减法 
{
    if(a==b)
    {
        return"0";
    }
    diao(a),diao(b);
    b+=zero(a.size()-b.size());
    int x=0;
    for(int i=0;i<a.size();i++)
    {
        int s=(a[i]-'0')-(b[i]-'0')-x;
        x=0;
        if(s<0)
        {
            x=1;
            s+=10;
        }
        a[i]=(s+'0'); 
    }
    for(int i=a.size()-1;i>=0;i--)
    {
        if(a[i]!='0')
        {
            a=a.substr(0,i+1);
            break;
        }
    }
    diao(a);
    return a;
}
string jia(string a,string b) //高精度加法 
{
	int www=0,eee=0;
	if(a[0]=='-')
	{
		www=1;
    	a=a.substr(1,a.size()-1);
	}
	if(b[0]=='-')
	{
		eee=1;
    	b=b.substr(1,b.size()-1);
	}
    if(a.size()>b.size()||(a.size()==b.size()&&a>b))
    {
    	swap(www,eee);
        swap(a,b);
    }
    int flag=0;
    if(www==1&&eee==1) 
    {
    	flag=1;
	}
	else if(eee==1)
	{
    	return '-'+jian(b,a);
	}
	else if(www==1)
	{
		return jian(b,a); 
	}
    diao(a),diao(b);
    a+=zero(b.size()-a.size()+1);
    b+="0";
    int x=0;
    for(int i=0;i<a.size()-1;i++)
    {
        int s=(a[i]-'0')+(b[i]-'0')+x;
        x=s/10;
        s%=10;
        a[i]=(s+'0'); 
    }
    a[a.size()-1]=(x+'0');
    if(a[a.size()-1]=='0')
    {
        a=a.substr(0,a.size()-1);
    }
    if(flag==1) a+='-';
    diao(a);
    return a;
}
string cheng(string a,string b) //高精度乘法 
{
	int www=0,eee=0;
	if(a[0]=='-')
	{
		www=1;
    	a=a.substr(1,a.size());
	}
	if(b[0]=='-')
	{
		eee=1;
    	b=b.substr(1,b.size());
	}
    int flag=0;
    if(a.size()>b.size())
    {
        swap(a,b);
    }
	if(www+eee==1)
	{
		flag=1;
	}
    diao(a),diao(b);
    int c[100000]={0};
    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<b.size();j++)
        {
            c[i+j]+=(a[i]-'0')*(b[j]-'0');
        }
    }
    for(int i=0;i<=b.size()*2;i++)
    {
        c[i+1]+=c[i]/10;
        c[i]%=10;
    }
    string s="";
    for(int i=b.size()*2;i>=0;i--)
    {
        if(c[i]!=0)
        {
            for(int j=0;j<=i;j++)
            {
                s+=(c[j]+'0');
            }
            break;
        }
    }
    diao(s);
    if(flag==1)
    {
    	string t=s;
    	s="-";
    	s+=t;
	}
    return s;
}
string zh(long long a)
{
	if(a==0) return "0";
	string s="";
	while(a!=0)
	{
		string t=s;
		s=(a%10+'0');
		s+=t;
		a/=10;
	}
	return s;
}
int main()
{
	getline(cin,str);
	int t=0;
	string flag="1",w="0",ans="0";
	//  正负  数 连加减 
	for(long long i=0;str[i]!='\0';i++)
	{
		if(str[i]=='+')
		{
			flag="1";
			if(i!=0&&str[i-1]=='+')
			{
				t++;
			}
		}
		if(str[i]=='-')
		{
			flag="-1";
			if(i!=0&&str[i-1]=='-')
			{
				t++;
			}
		}
		if(str[i]=='(')
		{
			i++;
			string x=dr(i);
			w=cheng(x,flag);
			i++;
			continue;
		}
		if(str[i]==')') continue;
		if(str[i]>='0'&&str[i]<='9')
		{
			if(str[i-1]==')')
			{
				string x=dr(i);
				ans=jia(ans,cheng(w,x));
				continue;
			}
			else
			{
				ans=jia(ans,cheng(flag,cheng(zh(t+1),dr(i))));
				t=0;
			}
		}
	}
	if(ans=="-0") ans="0";
	cout<<ans;
	return 0;
}
```

---

## 作者：快乐说话 (赞：1)

# 这是C++题解

显然，这道奶牛题的实质是通过题目要求的算式形式读入，以此要我们计算多个乘法乘积的和。

由于 _“不会出现如下几种形式：(1)23+++15-2、+23++(2)15-(1)2、23+++15-2+(0)100、23-(-3)15-2。”_ 所以在处理时可以就分为两种情况讨论：

1.没括号：统计加号（或减号）个数，和后面的数相乘，加（或减）到最终的答案中；

2.有括号：把括号内的数当做运算符的个数，然后和1同样操作。

显然，有如此长的算式的模拟题，没有字符串是难以操作的，所以直接把算式当做string读入是必要的。

由此可以得出以下代码
```cpp
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int i;//尽管不好，但由于很多操作较为繁琐，需要写成函数,而字符串的扫描大循环是计算的基础，不放在外面不好操作 
string s;//读入的算式 
void get(int &a)//得到被加（减）的数，需要带回去
{
	a=0;//不加会因为叠加问题而错误 
	for(;s[i]>='0'&&s[i]<='9';i++)//在下一个运算前所有的数字都是一个数，前面高位后面低位，先读高位，不断*10，把高位向高处挪，空出的高位留给小位
		a*=10,a=a+s[i]-'0';//直接加字符0会错得很惨 
}
int main(){
	int /*算式长度*/n,/*最终答案*/ans=0,/*符号个数*/t=0,/*运算数*/num=0,/*符号，如果是减号就就等于-1，如果是正数就是1*/nowf;
	cin>>s;
	n=s.length();
	if(s[0]>='0'&&s[0]<='9')s="+"+s;//最前面没有符号就相当于一个加号，可以加上，方便运算 
	for(i=0;i<n;i++)
	{
		if(s[i]=='+'||s[i]=='-')//数前面的运算符 
		{
			t++;
			if(s[i]=='+')nowf=1;
			if(s[i]=='-')nowf=-1;
		}
		else//如果前面的运算符数完了可以分情况讨论了 
		{
			if(s[i]>='0'&&s[i]<='9')//后面是运算数，第一种情况 
			{	
				get(num);//得到运算数 
				i--;//get函数会到第一个后面的运算符时返回，要减掉，不然后面会少数一个运算符 
				ans+=num*t*nowf;//加到答案里 
				num=t=0;//快乐置零 
			}
			if(s[i]=='(')//后面时括号，第二种情况 
			{
				i++;//从括号后的数开始数 
				get(t);
				i++;//跳过右括号才能搞运算数 
				get(num);
				i--; 
				ans+=t*num*nowf;
				num=t=0;
			}
		}
	}
	cout<<ans;//输出答案 
	return 0;
}
```

各种测试没有错误后提交，发现只有40分，第二个点错了，和后面的5个点也错了看底下的说明与提示：

### “算式长度不超过2000”

仔细想一想，发现如果是就减一个1999位的数那不要高精度不挂就怪了而且可能有高精负数，这会是一个浩大的工程。~~对于我这样的蒟蒻，不调个大半年肯定是出不来的，而对于大佬，高精？不是秒秒钟写出来的简单算法吗。~~

高精的写法在此不做过多阐述，只是说明要用哪些：

1.带负数高精度加(减)法:每次乘积加入答案；

2.带负数高精度乘法：运算符个数乘运算数；

3.高精度加单精度（高精度数加一）：上方所述第一种情况的运算符个数

以下是本蒟蒻的代码
```cpp
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
string s;
int i;
//不解释 
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
void add(int a[],int b[])//高精加法 
{
	int j,jw=0/*进位*/,c[2001]/*答案数组*/;
	for(j=0;j<=2000;j++)c[j]=0;
	c[0]=max(a[0],b[0]);
	for(j=1;j<=c[0];j++)
	{
		c[j]=a[j]+b[j]+jw;
		jw=c[j]/10;
		c[j]%=10;
	}
	if(jw>0)c[++c[0]]=jw;
	for(j=0;j<=c[0];j++)b[j]=c[j];
}
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
void add1(int a[],int x)//高精加单精 
{
    int j,jw=0;
    a[1]+=x;
    for(j=1;j<=a[0];j++)
    {
        a[j]+=jw;
        jw=a[j]/10;
        a[j]%=10;
    }
    if(jw>0)a[++a[0]]=jw;
}
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
void cheng(int a[],int b[],int c[])//乘法 
{
	int j,k;
	long long jw=0;
	for(j=0;j<=2000;j++)c[j]=0;
	c[0]=a[0]+b[0]-1;
	for(j=1;j<=a[0];j++)
		for(k=1;k<=b[0];k++)
			c[j+k-1]+=a[j]*b[k];
	for(j=1;j<=c[0];j++)
	{
		c[j]+=jw;
		jw=c[j]/10;
		c[j]%=10;
	}
	if(jw>0)
		while(jw>0)
		{
			c[++c[0]]=jw%10;
			jw/=10;
		}
}
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
void jian(int a[],int b[],int c[])//高精减法 
{
	int j,jw=0;
	for(j=0;j<=2000;j++)c[j]=0;	
	c[0]=max(a[0],b[0]);
	for(j=1;j<=c[0];j++)
	{
		c[j]=a[j]-b[j]-jw;
		jw=0;
		if(c[j]<0){jw=1; c[j]+=10;}
	}
	for(j=c[0];j>1&&c[j]==0;j--)c[0]--;	
}
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
void get(int a[])//不解释 
{
    int j;
    string number="";
    char c;
	//a=0;
	for(;s[i]>='0'&&s[i]<='9';i++)
	{
		c=s[i];
	    number=c+number;
	}
	a[0]=number.length();
	for(j=1;j<=a[0];j++)a[j]=number[j-1]-'0';
	//	a*=10,a=a+s[i]-'0';
}
//我是分割线---------------------------------------------------------------------------------------------------------------------------------------------
bool big(int a[],int b[])//为了解决负数和正数加减后是正是负的问题 
{
	int j;
	if(a[0]!=b[0])
		if(a[0]>b[0])return true;
			else return false;
	for(j=a[0];j>=1;j--)
	{
		if(a[j]>b[j])return true;
		if(a[j]<b[j])return false;
	}
	return true;
}
//我是分割线------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){
//	int n,ans=0,t=0,num=0,nowf;
    int n,nowf,zheng[2001],fu[2001],t[2001],num[2001],ans[2001],j,tt[2001];
    for(i=1;i<=2000;i++)num[i]=ans[i]=zheng[i]=fu[i]=t[i]=0;
    tt[0]=num[0]=ans[0]=zheng[0]=fu[0]=t[0]=1;
    tt[1]=num[1]=ans[1]=zheng[1]=fu[1]=t[1]=0;
	cin>>s;
	if(s[0]>='0'&&s[0]<='9')s="+"+s;
	n=s.length();
	for(i=0;i<n;i++)
	{
		if(s[i]=='+'||s[i]=='-')
		{
			add1(t,1);
			if(s[i]=='+')nowf=1;
			if(s[i]=='-')nowf=-1;
		}
		else
		{
			if(s[i]>='0'&&s[i]<='9')
			{	
				get(num);
				i--;
				cheng(t,num,tt);//	ans+=num*t*nowf;
				if(nowf==-1)add(tt,fu);
				if(nowf==1)add(tt,zheng);
				for(j=1;j<=2000;j++)
					tt[j]=t[j]=num[j]=0;
				tt[0]=t[0]=num[0]=1;//	t=0; num=0;
			}
			if(s[i]=='(')
			{
				i++;
				get(t);
				i++;
				get(num);
				i--;
				cheng(t,num,tt);
				//	ans+=t*num*nowf;
				if(nowf==-1)add(tt,fu);
				if(nowf==1)add(tt,zheng);
				for(j=1;j<=2000;j++)
					tt[j]=t[j]=num[j]=0;
				tt[0]=t[0]=num[0]=1;//	t=0; num=0;
			}
		}
	}
	if(big(zheng,fu))jian(zheng,fu,ans);
	else
	{
		cout<<'-';
		jian(fu,zheng,ans);
	}
	for(i=ans[0];i>=1;i--)cout<<ans[i];
//	cout<<ans;
	return 0;
}
```
### 以上便是本蒟蒻的题解的全部，请不要复制代码，多打这类长的模拟题可以提高任何人的代码能力。

---

## 作者：wanghaoyu1008 (赞：1)

这道题当然是一道模拟题，虽然压了点行，但我相信我写的程序可读性还是比较高的（毕竟还用了100多行），效率方面可能有点低，但不影响AC。重点在高精度（建议Luogu加一道高精度模板题）：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int L=2003;
const int S=1e6+6;

char s[L];
struct bgint{							//带符号大整数
	int l,a[S],p;
	void clr(){  						//clear
		memset(a,0,sizeof(a));l=0;p=1;
	}
	void plus(int &_l,int _a[]){ 		//两数绝对值相加
		int i;l=max(l,_l);
		for(i=1;i<=l;i++)a[i]+=_a[i];
		for(i=1;i<=l;i++)if(a[i]>9){a[i]-=10;a[i+1]+=1;}
		if(a[l+1])++l;
	}
	void minus(int &_l,int _a[]){		//两数绝对值相减
		int _p=1,i;
		if(l<_l)_p=-1;   				//可能减完要变号，这里提前变掉，免得一会进位麻烦
		if(l==_l)
			for(i=l;i>=1&&_p==1&&a[i]<=_a[i];i--)
				if(a[i]<_a[i])_p=-1;
		p*=_p;l=max(l,_l);
		for(i=1;i<=l;i++)
			a[i]=_p*(a[i]-_a[i]);
		for(i=1;i<=l;i++)if(a[i]<0){a[i]+=10;a[i+1]-=1;}
		while(l&&!a[l])--l;
	}
	void operator+=(bgint x){   		//带符号大整数相加
		if(p*x.p==1)plus(x.l,x.a);  	//同号
		else minus(x.l,x.a);			//异号
	}
	void operator*=(bgint x){   		//带符号大整数相加
		p*=x.p;
		int i,j,t;
		for(i=l;i>=1;i--){  			//此处没有另开变量，而是直接更新原数组的值
			t=a[i];a[i]=0;
			for(j=1;j<=x.l;j++)
				a[i+j-1]+=t*x.a[j];
		}
		l+=x.l-1;
		for(i=1;i<=l;i++){
			a[i+1]+=a[i]/10;
			a[i]%=10;
		}
		while(a[l+1]){
			++l;a[l+1]=a[l]/10;a[l]%=10;
		}
	}
	void multi(int x){  				//乘一个int
		int i;
		for(i=1;i<=l;i++)a[i]*=x;
		for(i=1;i<=l;i++){
			a[i+1]+=a[i]/10;
			a[i]%=10;
		}
		while(a[l+1]){
			++l;a[l+1]=a[l]/10;a[l]%=10;
		}
	}
	void init(int &x,int o){			//从字符串中读入
	    clr();p=o;  					//符号由调用者给出
		while('0'<=s[x]&&s[x]<='9'){a[++l]=s[x]-'0';++x;}
		for(int i=1;2*i<=l;i++)swap(a[i],a[l+1-i]);
        								//注意，按顺序读的是反的
	}
	void prnt(){						//输出
		if(l==0)printf("0");
		else if(p==-1)printf("-");
		for(int i=l;i>=1;i--)printf("%d",a[i]);printf("\n");
	}
}ans,t,n;
int m;

int main()
{
	scanf("%s",s);
	int i=0,l=strlen(s);
	ans.clr();
	if(s[0]!='+'&&s[0]!='-')
		ans.init(i,1);
	while(i<l){
		if(s[i]=='+'){
			++i;
			if(s[i]=='('){				//进行第二次改进
				++i;n.init(i,1);++i;
				t.init(i,1);t*=n;ans+=t;
			}
			else{						//没有进行第二次改进
				m=1;while(s[i]=='+'){++m;++i;}
			    t.init(i,1);t.multi(m);ans+=t;
			}
		}
		else{							//同上
			++i;
			if(s[i]=='('){
				++i;n.init(i,1);++i;
			    t.init(i,-1);t*=n;ans+=t;
			}
			else{
				m=1;while(s[i]=='-'){++m;++i;}
				t.init(i,-1);t.multi(m);ans+=t;
			}
		}
	}
	ans.prnt();
	return 0;
}
```

---

## 作者：xryjr233 (赞：1)

相比某些模拟题真的不算复杂。。。代码只有200多行。

需要注意这些地方:

读入字符停止的条件是一个不合法的字符,而这个字符可能是下一个部分的一部分(有点绕)，所以你需要保留这个字符。

这个表达式是可能有负数的，有两种处理方法:直接将负数运算放在结构体里，或者记录ans以及-ans，并且为了防止中途爆负，要调整运算顺序。

很明显第一种更加简便。

考虑负数的运算，设两个运算的变量的**绝对值**为a和b:

1.乘法，非常简单不细说。

2.减法，分五种情况,我们把他们都转为没有负号的加减法方便计算:

(-a)-(-b)，可以转化为b-a；

(-a)-b，可以转化为-(a+b)，a+b直接算，符号为负；

a-(-b)，可以转化为a+b直接算；

a-b，且a>=b，直接算；

a-b，且a<b，可以转化为-(b-a)直接算，符号为负。

3.加法，分四种情况：

(-a)+(-b)，可以转化为-(a+b)；

(-a)+b，可以转化为b-a，减法之前已经定义了；

a+(-b)，可以转化为a-b，减法之前已经定义了；

a+b直接算。

于是带负数的运算全被转化成了一些非负数运算和一些符号。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct bign{
	int n[2010],f;
}n,m,ans;
char op;
int tot;
void print(bign x){//输出 
	if(x.n[0]==0){
		putchar('0');
	}else{
		if(x.f==-1){
			putchar('-');
		}
		for(int i=x.n[0];i>=1;i--){
			printf("%d",x.n[i]);
		}
	}
}
void clear(bign &x){//清空 
	memset(x.n,0,sizeof(x.n));
}
bool operator >(bign x,bign y){//大于 
	if(x.f!=y.f){
		return x.f>y.f;
	}
	if(x.n[0]!=y.n[0]){
		return x.n[0]>y.n[0];
	}
	for(int i=x.n[0];i>=1;i--){
		if(x.n[i]!=y.n[i]){
			return x.n[i]>y.n[i];
		}
	}
	return false;
}
void operator ~(bign &x){//进位或退位 
	int w=0;
	for(int i=1;i<=x.n[0];i++){//退位 
		if(x.n[i]<0){
			x.n[i]+=10;
			x.n[i+1]--;
		}
	}
	for(;x.n[x.n[0]]==0&&x.n[0]>=1;x.n[0]--);
	for(int i=1;i<=x.n[0];i++){//进位 
		x.n[i]+=w;
		w=x.n[i]/10;
		x.n[i]%=10;
		if(w&&i==x.n[0]){
			x.n[0]++;
			x.n[x.n[0]]=0;
		}
	}
}
bign operator *(bign x,int y){//乘一个单精度整数 
	bign tmp=x;
	if(y<0){
		y=-y;
		tmp.f=-tmp.f;
	}
	for(int i=1;i<=x.n[0];i++){
		tmp.n[i]*=y;
	}
	~tmp;
	return tmp;
}
bign operator *(bign x,bign y){//高精度乘法 
	bign tmp;
	clear(tmp);
	if(x.f!=y.f){
		tmp.f=-1;
	}else{
		tmp.f=1;
	}
	tmp.n[0]=x.n[0]+y.n[0]-1;
	for(int i=1;i<=x.n[0];i++){
		for(int j=1;j<=y.n[0];j++){
			tmp.n[i+j-1]+=x.n[i]*y.n[j];
		}
	}
	~tmp;
	return tmp;
}
bign operator -(bign x,bign y){//减 
	bign tmp;
	clear(tmp);
	if(x.f==-1&&y.f==-1){
		x.f=1;
		y.f=1;
		tmp=y-x;
	}else if(x.f==-1){
		tmp.f=-1;
		tmp.n[0]=max(x.n[0],y.n[0]);
		for(int i=1;i<=tmp.n[0];i++){
			tmp.n[i]=x.n[i]+y.n[i];
		}
		~tmp;
	}else if(y.f==-1){
		tmp.f=1;
		tmp.n[0]=max(x.n[0],y.n[0]);
		for(int i=1;i<=tmp.n[0];i++){
			tmp.n[i]=x.n[i]+y.n[i];
		}
		~tmp;
	}else{
		if(y>x){
			tmp=y-x;
			tmp.f=-1;
		}else{
			tmp.f=1;
			tmp.n[0]=max(x.n[0],y.n[0]);
			for(int i=1;i<=tmp.n[0];i++){
				tmp.n[i]=x.n[i]-y.n[i];
			}
			~tmp;
		}
	}
	return tmp;
}
bign operator +(bign x,bign y){//加 
	bign tmp;
	clear(tmp);
	if(x.f==-1&&y.f==-1){
		x.f=1;
		y.f=1;
		tmp=x+y;
		tmp.f=-1;
	}else if(x.f==-1){
		x.f=1;
		tmp=y-x;
	}else if(y.f==-1){
		y.f=1;
		tmp=x-y;
	}else{
		tmp.f=1;
		tmp.n[0]=max(x.n[0],y.n[0]);
		for(int i=1;i<=tmp.n[0];i++){
			tmp.n[i]=x.n[i]+y.n[i];
		}
		~tmp;
	}
	return tmp;
}
char getnum(bign &x,char c){//读入一个数字并返回终止数字读入的字符(这个字符有可能是+或-) 
	string s="";
	x.f=1;
	if('1'<=c&&c<='9'){
		s+=c;
	}else if(c=='-'){
		x.f=-1;
	}
	c=getchar();
	while('0'<=c&&c<='9'){
		s+=c;
		c=getchar();
	}
	x.n[0]=s.size();
	for(int i=1;i<=x.n[0];i++){
		x.n[i]=s[x.n[0]-i]-'0';
	}
	return c;
}
int main(){
	while(1){
		if(!op){//如果之前没有+-就读入 
			op=getchar();
		}
		if(op!='-'&&op!='+'){//结束 
			break;
		}
		if(op=='+'){
			tot=0;
			while(op=='+'){
				tot++;
				op=getchar();
			}
			if(tot==1&&op=='('){//+(...)的表示方法 
				op=getnum(n,op);
				op=getnum(m,'0');
				ans=ans+(n*m);
			}else{//+++...的表示方法 
				op=getnum(n,op);
				ans=ans+(n*tot);
			}
		}else{
			tot=0;
			while(op=='-'){
				tot++;
				op=getchar();
			}
			if(tot==1&&op=='('){//-(...)的表示方法 
				op=getnum(n,op);
				op=getnum(m,'0');
				ans=ans-(n*m);
			}else{//---...的表示方法 
				op=getnum(n,op);
				ans=ans-(n*tot);
			}
		}
		if(op!='-'&&op!='+'){//如果之前的字符不是+-就在循环开始时读入 
			op=0;
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：21002tyj (赞：1)

【分析】

先咆哮……！！！

第一次写这么BT的高精~(BT当然是相对我而言、)

可以先把算式分成几个可以算出一个值的表达式（devide过程）

然后根据有无括号分成两类处理，有括号的可能为高精乘法。无括号的就不用啦

特别小心ans的正负与shu的正负，这里有4种情况，分别套用高精加减，符号单独处理。

【注意】

读入的字符串可能为0，读进来后要先判断其真实位数。

每一次高精减后也要用while判断真实位数。

开头可以没有符号，要特殊处理。没括号的情况下，依靠统计符号个数确定乘数，要特别小心。

注意初始化！！

然后几个高精代码要清晰- -


---

## 作者：Jsxts_ (赞：0)

~~硬核带负数高精度了解一下~~~~

我不会 $\text{python}$，所以用了高精度。

这道题对字符串的处理很简单，对于每一个数连着它的符号和个数分在一段，把每段的贡献加起来就好了。

操作大致分为以下三种：

1. 当 $s_i$ 是加号或减号时：此时我们要先把上一个数的贡献加入答案，再处理新数。在这时，后面只可能跟着一个括号里加一个数，或一串 “+” 或 “ - ”。对于括号的形式到下一类，这里如果有连续的符号，就累加当前数的个数就行了。
2. 当 $s_i$ 是左括号时：这时，括号里的数就是当前数的个数，所以记下来就行了。
3. 当 $s_i$ 是数字时：这个数一定是这一段中的原数（因为如果是个数就会在左括号那里处理），直接存进原数里就行。

代码：
```cpp
cnt = node();
cnt.a[1] = 1;
for (int i = 1;i <= len;i ++ ) {
	if (s[i] == '+' || s[i] == '-') {
		if (i > 1) {//统计上一个数的贡献
			node cc = mul2(num,cnt);
			if (zf == 1) ans = add(ans,cc);
			else ans = del(ans,cc);
		}
		zf = (s[i] == '+' ? 1 : -1);
		cnt = node();
		cnt.a[1] = 1;
		while (s[i+1] == '+' || s[i+1] == '-') cnt = add2(cnt,1), i ++;//"++..."的情况
	}
	else if (s[i] == '(') {
		i ++;
		cnt = node();
		while (s[i] >= '0' && s[i] <= '9') cnt = mul(cnt,10), cnt = add2(cnt,s[i]-'0'), i ++;//高精操作，感性理解，就是把数字存起来
	}
	else if (s[i] >= '0' && s[i] <= '9') {
		num = node();
		num.a[1] = s[i]-'0';
		while (s[i+1] >= '0' && s[i+1] <= '9') num = mul(num,10), num = add2(num,s[i+1]-'0'),i ++;
	}
}
node cc = mul2(num,cnt);//最后一个数也要算上
if (zf == 1) ans = add(ans,cc);
else ans = del(ans,cc);
```

然后就是高精度了。由于我没有想到分别存加和减这种方便、巧妙的方法，就硬写的一个带负数的高精（调了一中午）。具体细节看注释：

```cpp
struct node {//写成结构体更方便 
	int a[2010],zf;//正负tag 
	node(){memset(a,0,sizeof a);a[0] = zf = 1;}
	void print() {
		if (zf < 0) putchar('-');
		for (int i = a[0];i;i -- ) printf("%d",a[i]);
		puts("");
	}
	friend bool operator < (node &x,node &y) {//比较（注意正负的影响） 
		if (x.zf < 0 && y.zf > 0) return 1;
		if (x.zf > 0 && y.zf < 0) return 0;
		int t = x.zf < 0;
		if (x.a[0] > y.a[0]) return t;
		if (x.a[0] < y.a[0]) return !t;
		for (int i = x.a[0];i;i -- ) {
			if (x.a[i] > y.a[i]) return t;
			if (x.a[i] < y.a[i]) return !t;
		}
		return 1;
	}
}ans;
node del(node a,node b);
node add(node a,node b) {//高精加高精，这里b肯定是正数 
	node c;
	if (a.zf < 0) {//a不是正数，那么a的绝对值大于b的话是负数，否则是正数 
		a.zf = 1;//绝对值 
		if (a < b) {
			c = del(b,a), c.zf = 1;
			return c;
		}
		else {
			c = del(a,b), c.zf = -1;
			return c;
		}
	}
	c.a[0] = max(a.a[0],b.a[0]);//常规高精 
	for (int i = 1;i <= c.a[0];i ++ ) {
		c.a[i] += a.a[i] + b.a[i];
		if (c.a[i] >= 10) c.a[i+1] ++, c.a[i] -= 10;
	}
	while (c.a[c.a[0]+1]) c.a[0] ++;
	return c;
}
node add2(node a,int b) {//高精+低精，没啥好说 
	node c = a;
	c.a[1] += b;
	for (int i = 1;i <= c.a[0];i ++ ) {
		if (c.a[i] >= 10) c.a[i+1] ++, c.a[i] -= 10;
	}
	while (c.a[c.a[0]+1]) c.a[0] ++;
	return c;
}
node mul(node a,int b) {//高精乘低精，也没啥好说 
	node c;
	c.a[0] = a.a[0];
	for (int i = 1;i <= c.a[0];i ++ ) {
		c.a[i] += a.a[i] * b;
		if (c.a[i] >= 10) c.a[i+1] += c.a[i]/10, c.a[i] %= 10;
	}
	while (c.a[c.a[0]+1]) {
		if (c.a[c.a[0]+1] >= 10) c.a[c.a[0]+2] += c.a[c.a[0]+1] / 10, c.a[c.a[0]+1] %= 10;
		c.a[0] ++;
	}
//	c.print();
	return c;
}
node del(node a,node b) {//高精-高精 
	node c;
	int fl = 1;
	if (a < b) {
		if (a.zf < 0) {//a是负数，结果就是绝对值之和的相反数 
			a.zf = 1;
			c = add(a,b), c.zf = -1;
			return c;
		}
		else swap(a,b), fl = -1;//交换相减 
	}
	for (int i = 1;i <= a.a[0];i ++ ) {
		c.a[i] += a.a[i] - b.a[i];
		if (c.a[i] < 0) c.a[i+1] --, c.a[i] += 10;
	}
	c.a[0] = a.a[0], c.zf = fl;//更新符号 
	while (!c.a[c.a[0]] && c.a[0] > 1) c.a[0] --;
	if (c.a[1] == 0 && c.a[0] == 1) c.zf = 1;//注意，这个数为0时是算正的！ 
	return c;
}
node mul2(node a,node b) {//高精乘高精 
	node c;
	c.a[0] = a.a[0] + b.a[0] - 1;
	for (int i = 1;i <= a.a[0];i ++ ) {
		for (int j = 1;j <= b.a[0];j ++ ) {
			c.a[i+j-1] += a.a[i] * b.a[j];
		}
	}
	for (int i = 1;i <= c.a[0];i ++ ) {
		if (c.a[i] >= 10) c.a[i+1] += c.a[i] / 10, c.a[i] %= 10;
	}
	while (c.a[c.a[0]+1]) {
		if (c.a[c.a[0]+1] >= 10) c.a[c.a[0]+2] += c.a[c.a[0]+1] / 10, c.a[c.a[0]+1] %= 10;
		c.a[0] ++;
	}
//	c.print();
	return c;
}
```
这个高精可以作为模板使用，效率应该还行（吧

然后就做完了，是锻炼码力和细节的好题。

---

## 作者：华为2X (赞：0)




今早突然想写这道题，然后写了两节课只得了10分[大哭]！！！

然后求助神犇老师[@selar2017](https://www.luogu.org/space/show?uid=79254)，神犇经过一下午的调试，ACACACAC！！！

看到题解和AC这么少，我就知道我的机会来了！


===============================分割线===============================

题目本身很容易理解，主要是对细节的处理，下面的算法主要是对+、-和*进行重载，变为高精度算法

附AC代码
```cpp
#include <iostream>
#include<cstring>
using namespace std;
const int MAXN = 4000;
char a[202];
class bign
{ 	private:
	int len,s[MAXN];
  	public:
  //预说明三个构造函数。构造函数没有返回值
	bign();//无参数构造函数，一定要有
	bign(int num); 
	bign(char num[], int n);
  //类成员函数  
	void show();//预说明，定义在外部
	int getlen()//在类内部可以定义函数
	{return len;}
	int cm(bign a);//比较ans和a的大小，返回-1,0,1
	bign operator+(const bign &b) const;
	bign operator*(const bign &b) const;
	bign operator-(const bign &b) const;//重载+、-、*； 
};
void bign::show()//类外定义类的成员函数，用于输出
{
	for(int i=len-1;i>=0;i--)
	 cout<<s[i];
	return;
}
bign::bign()
{ 
	memset(s,0,sizeof(s));
	len = 1;
	return;
} 
bign::bign (int num) //将整形转换为字符串并记录长度
{ 
	memset(s,0,sizeof(s));
	len=1;
	int i; 
	for(i=0;num>0;i++)
     { 
	  s[i]=num%10;
	  num/=10;
	 }
	len=i;
	return;
}
bign::bign(char num[], int n)//用字符串的构造函数
{
	memset(s,0,sizeof(s));
	len=1;
	for(int i=0;i<n;i++)
	 s[i]=int(num[n-1-i])-48;
	len=n;
	return;
}
bign bign::operator+(const bign &b) const //高精度加法 
{
	bign c(0);
	int i,g;
	int maxlen=len>b.len?len:b.len;
	for( i=0,g=0;i<maxlen+2;i++)
	 {
	  c.s[i]=s[i]+b.s[i]+g;
	  g=c.s[i]/10;
	  c.s[i]%=10;
	 }
	c.len=c.s[maxlen]>0?maxlen+1:maxlen;
	return c;
} 
bign bign::operator* (const bign &b) const //高精度乘法 
{
	bign c(0);
	int g;
	for(int i = 0; i < len; i++)  
     {
	  g=0;
	  for(int j = 0; j < b.len+2; j++)  
	   {
	    c.s[i+j] =c.s[i+j]+ s[i] * b.s[j]+g;  
		g=c.s[i+j]/10;
		c.s[i+j]%=10;
	   }
     }
	c.len=c.s[len+b.len-1]>0?len+b.len:len+b.len-1;
	return c;
}
bign bign::operator -(const bign &b) const //高精度减法 
{
	int g=0;
	bign c;
	c.len=len;
	for(int i=0;i<len;i++)
	 {
	  c.s[i]=s[i]-b.s[i]-g;
	  if(c.s[i]<0) 
	   {
	    c.s[i]=c.s[i]+10;
		g=1;
	   }
	  else
	   g=0; 
	 }
	while(c.s[c.len-1]==0&&c.len>=2)
	 c.len--;//去0操作，删去前导0
	return c;
}
int  bign::cm(bign a)//比较两个字符串的大小 
{ 
	if(len!=a.len) 
	 {
	  if(len>a.len)
	   return 1;
	  else
	   return -1;
	 }	
	else
	 {
	  int i=len;
	  while(s[i]==a.s[i]&&i>=0)
	   i--;
	  if(i<0)
	   return 0;
	  else
	   {
	    if(s[i]>a.s[i])
	     return 1;
	    else
	     return -1;
	   }
	 }
}
bign readbign(int i)
{ 
    char b[200];
	int j=0;
	while('0'<=a[i]&&a[i]<='9' )
	 {
	  b[j]=a[i];
	  j++;
	  i++;
	 }
	b[j+1]='\0';
	bign x(b,j);
	return x;
}
int num=0;
int main()
{ 
  	cin>>a;//输入不多说 
 	int i=0,flag=0;//i遍历长度，flag判断正负（1为-，0为+） 
  	bign ans;//答案，ans仅记录答案的绝对值 
  	while(a[i]!='\0')
     {
	  if('0'<=a[i]&&a[i]<='9')//仅用于开头直接是数字时 
       {
	    bign x=readbign(i);//获得高精度数字 
	    i=i+x.getlen();//遍历位置++ 
		if(flag==0)
		 ans=ans+x;
/*		num++;
		cout<<num<<":",ans.show(),cout<<endl;*/
/*		else
		 {
		  if(ans.cm(x)>0)
		   ans=ans-x;
		  else
		   {
		    ans=x-ans;
			flag=0;
		   }
		 }*/
//经过我的判断，这段代码并不需要 
	  }
      else
	   {
	    if(a[i]=='+')
	     {
	      bign y(1);//处理加号情况 
		  if(a[i+1]=='+')//多个加号的运算 
		   {
		    int add=0;//记录add的个数 
			while(a[i]=='+')
			 i++,add++;
			bign k(add);//将add转化为字符串
			y=k;
		   }
		  else
		   {
		   	if(a[i+1]=='(')
		   	 {
		      i=i+2;
			  y=readbign(i);
			  i=y.getlen()+i;
			  i++;
			 }
			else
			 i++;
		   }
		  bign x=readbign(i);//获取+后面的数字 
		  i=i+x.getlen();
		  bign z=x*y;//高精度乘法 
		  if(flag==0)//判断ans是否为正 
		   ans=ans+z;
		  else
		   {
			if(ans.cm(z)>0)//ans为负数，且ans的绝对值大于z的绝对值 
			 ans=ans-z;
			else 
			 {
			  flag=0;//小负减大负，符号为正 
			  ans=z-ans;
			 }
		   }
/*		  num++;
		  cout<<num<<":",ans.show(),cout<<endl; */
		 }
		else
		 {
	      bign y(1);//处理加号情况 
		  if(a[i+1]=='-')//多个加号的运算 
		   {
		    int sub=0;//记录sub的个数 
			while(a[i]=='-')
			 i++,sub++;
			bign k(sub);//将sub转化为字符串
			y=k;
		   }
		  else
		   {
		   	if(a[i+1]=='(')
		   	 {
		      i=i+2;
			  y=readbign(i);
			  i=y.getlen()+i;
			  i++;
			 }
			else
			 i++;
		   }
		  bign x=readbign(i);//获取-后面的数字 
		  i=i+x.getlen();
		  bign z=x*y;//高精度乘法 
		  if(flag==1)//判断ans是否为负 
		   ans=ans+z;
		  else
		   {
			if(ans.cm(z)>=0)//ans为正数，且ans大于z
			 ans=ans-z;
			else 
			 {
			  flag=1;//小数减大数，符号为负 
			  ans=z-ans;
			 }
		   }
/*		  num++;
		  cout<<num<<":",ans.show(),cout<<endl; */
		 }
	   }
	 }
  if(flag==1)
   cout<<'-';
  ans.show();  
}

```

---

