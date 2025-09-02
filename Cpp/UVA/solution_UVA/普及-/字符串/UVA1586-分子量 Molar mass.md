# 分子量 Molar mass

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4461

[PDF](https://uva.onlinejudge.org/external/15/p1586.pdf)

## 样例 #1

### 输入

```
4
C
C6H5OH
NH2CH2COOH
C12H22O11```

### 输出

```
12.010
94.108
75.070
342.296```

# 题解

## 作者：Zlc晨鑫 (赞：15)

作为一个还没学过的化学的初一党，我不得不自行查询资料，了解分子式是什么东西之后才做得了此题。所以，我把计算分子量的方法先写出来。（没学过化学，大佬们请指出错误）

注意，原子量和分子量是不一样，一个分子可以有多个原子组成，其形式大概由一个大写字母（原子）和一个下标（就是右下角的那个数字，表示包含该原子的个数）组成。题目中已经说了，数字是前一个字母的下标。

分子式的百度百科[分子式](https://baike.baidu.com/item/%E5%88%86%E5%AD%90%E5%BC%8F)。

如果你**认真**看了[PDF](https://onlinejudge.org/external/15/p1586.pdf)的话，应该会发现一些细节：
1. 下标可以是多位数！（不只有一位！所以在判断不能简单地判断下一位）
2. 下标是1时省略。
3. 输出要保留三位小数（看样例应该看得出来吧）。

最后再说一下输出格式的问题：一行**一个**小数！

再来看看一组数据：

C6H5OH

这个分子式的分子量是：6个C原子 + 5个H原子 + 1个O原子 + 1个H原子。

[PDF](https://onlinejudge.org/external/15/p1586.pdf)里面有每个原子的原子量（似乎题意翻译里面的多出了一位小数），照着计算就可以了。

下面给出AC代码：

```cpp
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

// 判断一个字符是不是数字
bool is_number(char ch)
{
    if (ch >= '0' && ch <= '9') return true;
    else return false;
}

// 根据题意获取原子量
double get_value(char ch)
{
    if (ch == 'C') return 12.01;
    if (ch == 'H') return 1.008;
    if (ch == 'O') return 16.00;
    if (ch == 'N') return 14.01;
    return 0.0;
}

int main(void)
{
    string s;
    // N组数据
    int n;
    scanf("%d", &n);
    while (n--)
    {
        cin >> s;
        double sum = 0;
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
        	// 如果当前字符是数字，就不用计算了，直接进入下一次循环
            if (is_number(s[i])) continue;
            // 如果下一位还是字母，就直接加上一个原子量即可
            else if (!is_number(s[i + 1])) sum += get_value(s[i]);
            // 有下标的情况
            else
            {
            	// 下标的数值
                int x = 0;
                // 将字符串转化为数值
                for (int j = i + 1; is_number(s[j]); j++)
                    x = x * 10 + (s[j] - '0');
                sum += get_value(s[i]) * x;
            }
        }
        // 保留三位小数输出
        printf("%.3lf\n", sum);
    }
    return 0;
}
```

---

## 作者：Anguei (赞：8)

这道题现有题解非常麻烦，我一定要写个简单的。

思路：把每个相对原子质量的质量映射到一个 map 里面，然后读如字符串并遍历，找出每个原子及其个数，与映射表的质量相乘，再累加一下即可得出结果。

注意，对于最后一个字符需要特判是否为原子，若是，要再加上它的质量。

**使用 cctype 头文件可以简化代码！**

$O(n^2)$的暴力算法，在 $3s$ 应对 $8000$ 的数据，还是没什么问题的。

```cpp
//【UVA1586】Molar mass - 洛谷 - Ac
#include <cstdio>
#include <cctype>

#include <map>
#include <string>
#include <iostream>

int main() {
	int T;
	std::cin >> T;
	std::map<char, double> map;
    // 映射
	map['C'] = 12.01;
	map['H'] = 1.008;
	map['O'] = 16.00;
	map['N'] = 14.01;
	while (T--) {
		std::string s;
		std::cin >> s;
		double ans = 0;
		for (int i = 0; i < s.size(); ++i)
			if (isalpha(s[i])) {
				int num = 0;
				if (!isalpha(s[i + 1])) {
					for (int j = i + 1; j < s.size(); ++j)
						if (isdigit(s[j]))
							num = num * 10 + s[j] - 48; // 找个数
						else
							break;
					ans += map[s[i]] * num; //先相乘再累加
				} 
				else
					ans += map[s[i]] * (num = 1); // 只有字母的情况
				//std::clog << num << " ";
			}
		if (isalpha(s.back())) // 最后的特判
			ans += map[s.back()];
		std::printf("%.3f\n", ans);
	}
}
```

---

## 作者：swl3992 (赞：3)

说句实话，
# 我真的看不懂大佬们写的题解
### 本蒟蒻自己来发一篇


其实本蒟蒻刚开始连题目都看不懂，后来才发现是统计元素个数并乘上相应的值(本句化学大佬勿看)

使用map可以简化程序

不多说，上代码(本蒟蒻有一个癖好，if,for,while等不管有几句话都要加大括号)，代码很短，去掉大括号也就30~40行

```cpp
#include <bits/stdc++.h>	//万能头文件
using namespace std;
map<char,double> mp;	//一个映射，关键字为char,值为double
int main()
{
	ios::sync_with_stdio(0);	//cin,cout加速，取消与printf和scanf同步
	mp['C']=12.01;	//将各个元素映射为值
	mp['H']=1.008;
	mp['O']=16.00;
	mp['N']=14.01;
	int n;
	cin>>n;
	while(n--)	//n组数据
	{
		string str;
		cin>>str;	//读入
		double ams=0;	//本人喜欢把ans写成ams
		for(int i=0;i<str.size();i++)	//过一遍
		{
			if((str[i]=='C')||(str[i]=='H')||(str[i]=='O')||(str[i]=='N'))	//如果是一个元素(一个或多个都可以，后面会解释)
			{
				ams+=mp[str[i]];	//加上相应的值
			}
			else	//数字
			{
				int num=0;
				int j=i-1;	//需要储存当前字母
				while(i<str.size()&&str[i]>='0'&&str[i]<='9')	//找出所有数字
				{
					num=num*10+str[i]-'0';	//累加
					i++;	//++
				}
				i--;	//由于最后是先i++再while循环结束，所以要--回上一个
				ams=ams+((num-1)*mp[str[j]]);	//由于如果是多个，会在遇到字母时就加上一个，所以要-1
			}
		}
		printf("%.3lf\n",ams);	//记得保留三位小数
	}
	return 0;
}

```

不知是窝太蒟了还是怎么，窝怎么也看不懂大佬们的题解

---

## 作者：哔哩哔哩 (赞：3)

感觉大家写的码风都好奇怪啊

我来一个可读性高的

> 加一个打表可能会操作简单一点

## 思路
对于每一个化学元素，打表算质量

对于后面跟着的数字，可以用读入优化的思想来求

（为什么那么多题目都是让我们求相对分子质量啊QAQ）

这题还算简单，如果会了的话推荐大家打一下稍微难了那么一点点的（加了个栈 映射什么的）[P2382](https://www.luogu.org/problemnew/show/P2382)

## 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double w[]={12.01,1.008,16.00,14.01};
string a;
double score;
int main()
{
	int T;cin>>T;
	while(T--)
	{
		cin>>a;
		score=0.0;
    	for(int i=0;i<a.size();i++)
    	{
    		double tot=0.0;
    		if(a[i]=='C') 
			{
				int res=0;
				while(a[i+1]>='0'&&a[i+1]<='9')
				{
					res=res*10+a[i+1]-'0';
					i++;
				}
				if(res!=0)tot=double(w[0]*res);
				else tot=w[0];
			}
    		if(a[i]=='H')
			{
				int res=0;
				while(a[i+1]>='0'&&a[i+1]<='9')
				{
					res=res*10+a[i+1]-'0';
					i++;
				}
				if(res!=0)tot=double(w[1]*res);
				else tot=w[1];
			}
    		if(a[i]=='O')
			{
				int res=0;
				while(a[i+1]>='0'&&a[i+1]<='9')
				{
					res=res*10+a[i+1]-'0';
					i++;
				}
				if(res!=0)tot=double(w[2]*res);
				else tot=w[2];
			}
    		if(a[i]=='N')
			{
				int res=0;
				while(a[i+1]>='0'&&a[i+1]<='9')
				{
					res=res*10+a[i+1]-'0';
					i++;
				}
				if(res!=0)tot=double(w[3]*res);
				else tot=w[3];
			}
    		score+=tot;
		}
		printf("%.3lf\n",score);
	}
    return 0;
}
```
不多写注释了，感觉很容易懂的

---

## 作者：Snowlanuck (赞：1)

判断字符,如果是字母就读取后面的数字,把字母代表的数字 乘 后面的数字 累加到结果就OK了

本题的难点其实是数字的位数不确定,所以要读取完整的数字才行

我的程序如果遇到末尾也是数字的情况,会直接读越界,所以直接多开了个P元素一直放在末尾,意味着"STOP",也算是小小的偷鸡吧,这样就不用写其他的判断了,这样做也不需要特判末尾了

下面放代码

```cpp
//#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
int main()
{
	map<char, float> Map =
	{
		{'C',12.01f},
		{'H',1.008f},
		{'O',16.00f},
		{'N',14.01f},
		{'P',0.0f} //偷鸡
	};

	int n, Length;
	cin >> n;
	while (n--)
	{
		string str;
		cin >> str;
		str += 'P'; //偷鸡
		Length = str.length();
		float Res = 0;
		for (int i = 0; i < Length - 1; i++)
		{
			if (isalpha(str[i]))
			{//判断当前字符是否为字母
				if (!isalpha(str[i + 1]))
				{//判断下一位是否为数字
					float Num = Map[str[i]];
					int t = (str[++i] - '0');
					while (!isalpha(str[++i])) //找到完整的数字
						t = t * 10 + (str[i] - '0');
					i--;
					Res += (Num * t);
				}
				else { Res += Map[str[i]]; } //如果下一位不是数字直接加即可
			}
		}
		printf("%.3f\n", Res);
	}
	return 0;
}

```


---

## 作者：hzg0226 (赞：1)

* 有点绕弯子，需要先到好的思路才行。
* 根据分子式的特点，每一个原子后面都会有其对应的个数，只不过当个数为1时省略了。
* 所以每次都以一个原子为标准，判断其后面的情况即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

map<char, float> atom;

int main()
{
    //freopen("in.txt", "r", stdin);
    atom['C'] = 12.01;atom['H'] = 1.008;atom['O'] = 16.00;atom['N'] = 14.01;
    int n;cin>>n;
    while(n--){
        string fenzishi;cin>>fenzishi; // 保存分子式
        float sum=0; // 分子量
        // 每一个分子，后面都为其个数，只不过当个数为1时，1被省略了
        // 每次都以一个原子为标准，判断其后面的情况
        for(int pos=0;pos<fenzishi.size();pos++){
            char yuansu = fenzishi[pos]; // 当前原子
            if(pos+1==fenzishi.size() || isalpha(fenzishi[pos+1])){ // 原子为最后一个或者下一个仍然为原子，故该原子下标为1
                sum += atom[yuansu];
            }
            else{ // 下一个为数字，则表示该原子个数不为1
                int num=0;
                while(pos+1!=fenzishi.size() && isdigit(fenzishi[pos+1])){
                    num = num*10+(fenzishi[pos+1]-'0');
                    pos++;
                }
                sum += atom[yuansu]*num;
            }
        }
        printf("%.3f\n", sum);
    }
    return 0;
}
```

---

## 作者：EnderXie (赞：0)

看到这么多长题解，自己来发一个短的~

思路：

1.整行读入输入，再一位一位读，若为分子就向后读一个数字；
2.将数字记录下来；
3.计算。

上代码：

```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
#define _for(i,a,b) for(int i=a;i<b;i++)
using namespace std;
int num,list[4]={},ind=0;
string input,line="CHON";
double mass=0,anss[1001]={};
int main(){
	cin>>num;
	_for(i,0,num){
		memset(list,0,sizeof(list));//记得重置数组！
		cin>>input;
		mass=0.0;
		_for(i,0,input.size()){
			if('A'<=input[i] && input[i]<='Z'){
				int num=0;
				char ele=input[i];//直接假设下一位就是字母
                while('0'<=input[i+1] && input[i+1]<='9' && i+1<input.size()){
					num=num*10+(input[i+1]-'0');
					i++;//这里是读入一个整数的代码
				}
				if(num==0) num=1;
				list[line.find(ele)]+=num;
			}
		}
		mass=list[0]*12.01+list[1]*1.008+list[2]*16.00+list[3]*14.01;
		anss[ind++]=mass;
	}
	_for(i,0,num) cout<<fixed<<setprecision(3)<<anss[i]<<endl;
	return 0;
}
```

最后，记得保留三位小数！！！

---

## 作者：sss7020 (赞：0)

```
#include<iostream>
#include<sstream>
#include<string>
#include<cctype>
#include<iomanip>
using namespace std;
int main(){
	string s;//输入的字符串
	int kase;
	cin>>kase;
	while(kase--){
		cin>>s;
		string s2;//之后改成的字符串
		if(isalpha(s[s.length()-1]))s+="1";
        //不要让这个字符串的末尾是字母
		for(int i=0;i<s.length();i++){
			s2+=s[i];
			if(isdigit(s[i])){
				if(i==s.length()-1)continue;
                //如果到了最后一个，就不要看了，会溢出
				if(isalpha(s[i+1]))s2+=' ';
                //为什么这样做，马上揭晓
                //如果下一个是字母，后面加个空格
				else continue;
				//否则跳过（下一个是数字）
			}
			else if(isalpha(s[i])){
				if(isalpha(s[i+1]))s2+=" 1 ";
                //如果下一个是数字，后面加个 1 
				else s2+=" ";
                //否则直接加空格
			}
		}//用来把字符串改成字母 数字 的格式。
		//cout<<s2<<endl;
		stringstream ss(s2);//宁愿这样做
		int n;
		char c;
		double ans=0.0;
		while(ss>>c>>n){
			switch(c){
				case('C'):ans+=12.01*n;break;
				case('H'):ans+=1.008*n;break;
				case('O'):ans+=16.00*n;break;
				case('N'):ans+=14.01*n;break;
			}//判断
			//cout<<fixed<<setprecision(3)<<ans<<endl;
		}
		cout<<fixed<<setprecision(3)<<ans<<endl;
        //保留三位小数输出。
	}
	return 0;
}
```

---

## 作者：Punny (赞：0)

**这边打了个表直接水过了。。**

本题由我提供翻译，欢迎大家指出错误。
```cpp
#include<bits/stdc++.h>
using namespace std;
double a[200],ans,x,w;
int n;
int main()
{
    a[67]=12.01;
    a[72]=1.008;
    a[79]=16.00;
    a[78]=14.01;
    scanf("%d",&n);
    for(int j=1;j<=n;j++)
    {
    ans=0;
    string s;
    cin>>s;
    int len=s.length();
    if(len==1)
    {
    printf("%.3lf\n",a[(int)s[0]]);
    continue;
    }
        for(int i=0;i<len;i++)
        {
            if(67<=(int)s[i]&&(int)s[i]<=79)
            {
                x=a[(int)s[i]];
                if((67<=(int)s[i+1]&&(int)s[i+1]<=79))
                {
                    ans+=x;
                }
            }
            else
            {
                if(49<=(int)s[i]&&(int)s[i]<=57)
                    w=w*10.0+(s[i]-'0');
                if((67<=(int)s[i+1]&&(int)s[i+1]<=79)||i+1==len)
                {
                    ans+=x*w;
                    w=0;
                }
            }
        }
        if((67<=(int)s[len-1]&&(int)s[len-1]<=79))
        printf("%.3lf\n",ans+a[(int)s[len-1]]);
        else
        printf("%.3lf\n",ans);
    }
}
```
本题的分子式是没括号的，有括号会难一些。保留三位小数输出。

---

## 作者：PC_DOS (赞：0)

其实这道题和[P1944-有机物燃烧](https://www.luogu.org/problemnew/show/P1994)有异曲同工之妙，都是统计一下输入分子式之中各种元素的个数。

统计时，从头到尾遍历字符串，如果发现元素符号，且它的后面不是数字或者这个字符位于字符串末尾，那么对应的元素个数加一，如果它的后面是数字，那么逐个读取这些数字，直到遇到非数字字符或者到达字符串末尾为止，将读取到的数字字符串转化为整数并加到记录对应元素个数的计数器上即可。

统计完成后，根据题目所给原子量计算分子量(数值上等于题目所要求的摩尔质量)并输出即可。输出后务必注意清空记录元素个数的计数器。

代码:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std; //头文件和命名空间
string strReverse(string strOrigin){ //字符串倒转函数
	if (strOrigin.length() == 0){
		return "";
	}
	long long i;
	string ans;
	for (i = strOrigin.length() - 1; i >= 0; --i) ans += strOrigin[i];
	return ans;
}
long long ToInt(string sNumber){ //字符串转为整数(支持负数，不支持小数，遇到非法字符视为该位为0)的函数
	long long i;
	long long lRet = 0;
	if (sNumber.length() == 0)
		return 0;
	sNumber = strReverse(sNumber);
	if (sNumber[sNumber.length() - 1] == '-'){
		for (i = 0; i <= sNumber.length() - 2; ++i)
			if ('0' <= sNumber[i] && sNumber[i] <= '9')lRet += (sNumber[i] - '0')*pow(10, i);
		return -lRet;
	}
	else{
		for (i = 0; i <= sNumber.length() - 1; ++i)
			if ('0' <= sNumber[i] && sNumber[i] <= '9')lRet += (sNumber[i] - '0')*pow(10, i);
		return lRet;
	}
}
inline bool IsNum(char chrTest){ //判断一个字符是不是数字的函数
	return (chrTest >= '0' && chrTest <= '9');
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int nH = 0, nO = 0, nC = 0,nN=0; //存放氢(H)氧(O)碳(C)氮(N)原子的个数
	double dMass=0; //存放分子量
	string sCompound, sTemp(""); //sCompound-输入的化合物；sTemp-暂存读取的数字字符串
	int i, j, k, nCount, iLength; //i、j、k-循环变量；nCount-询问的个数；iLength-输入字符串的长度
	cin >> nCount; //读入询问个数
	for (k = 1; k <= nCount; ++k){ //接受询问
		cin >> sCompound; //读入分子式
		iLength = sCompound.length() - 1; //计算长度
		for (i = 0; i <= iLength; ++i){ //从头到尾遍历字符串
			if (sCompound[i] == 'C'){ //发现碳
				if (i == iLength){ //如果位于字符串末尾
					++nC; //对应原子数加一
					continue; //继续循环
				}
				if (IsNum(sCompound[i + 1])){ //如果它的后面是数字
					for (j = i + 1; IsNum(sCompound[j]) && j <= iLength; ++j){ //逐个读取这些数字，直到遇到非数字字符或者到达字符串末尾为止
						sTemp += sCompound[j];
					}
					nC += ToInt(sTemp); //将读取到的数字字符串转化为整数并加到记录对应元素个数的计数器上
					sTemp = ""; //清空暂存字符串
				}
				else{ //如果它的后面不是数字
					++nC; //对应原子数加一
					continue; //继续循环
				}
			}
			else if (sCompound[i] == 'H'){ //发现氢
				if (i == iLength){ //如果位于字符串末尾
					++nH; //对应原子数加一
					continue; //继续循环
				}
				if (IsNum(sCompound[i + 1])){ //如果它的后面是数字
					for (j = i + 1; IsNum(sCompound[j]) && j <= iLength; ++j){ //逐个读取这些数字，直到遇到非数字字符或者到达字符串末尾为止
						sTemp += sCompound[j];
					}
					nH += ToInt(sTemp); //将读取到的数字字符串转化为整数并加到记录对应元素个数的计数器上
					sTemp = ""; //清空暂存字符串
				}
				else{ //如果它的后面不是数字
					++nH; //对应原子数加一
					continue; //继续循环
				}
			}
			else if (sCompound[i] == 'O'){ //发现氧
				if (i == iLength){
					++nO; //对应原子数加一
					continue; //继续循环
				}
				if (IsNum(sCompound[i + 1])){ //如果它的后面是数字
					for (j = i + 1; IsNum(sCompound[j]) && j <= iLength; ++j){ //逐个读取这些数字，直到遇到非数字字符或者到达字符串末尾为止
						sTemp += sCompound[j];
					}
					nO += ToInt(sTemp); //将读取到的数字字符串转化为整数并加到记录对应元素个数的计数器上
					sTemp = ""; //清空暂存字符串
				}
				else{ //如果它的后面不是数字
					++nO; //对应原子数加一
					continue; //继续循环
				}
			}
			else if (sCompound[i] == 'N'){ //发现氮
				if (i == iLength){
					++nN; //对应原子数加一
					continue; //继续循环
				}
				if (IsNum(sCompound[i + 1])){ //如果它的后面是数字
					for (j = i + 1; IsNum(sCompound[j]) && j <= iLength; ++j){ //逐个读取这些数字，直到遇到非数字字符或者到达字符串末尾为止
						sTemp += sCompound[j];
					}
					nN += ToInt(sTemp); //将读取到的数字字符串转化为整数并加到记录对应元素个数的计数器上
					sTemp = ""; //清空暂存字符串
				}
				else{ //如果它的后面不是数字
					++nN; //对应原子数加一
					continue; //继续循环
				}
			}
			else{
				continue; //继续循环
			}
		}
		dMass = nH*1.008 + nC*12.01 + nO*16.00 + nN*14.01; //计算分子量
		cout.setf(ios::fixed); //设置定点输出
		cout << setprecision(3) << dMass << endl; //输出分子量，保留三位小数
		nH = 0;
		nC = 0;
		nO = 0;
		nN = 0; //输出后务必注意清空记录元素个数的计数器
	}
	return 0; //结束
}
```

---

