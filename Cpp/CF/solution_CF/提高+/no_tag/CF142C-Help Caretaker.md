# Help Caretaker

## 题目描述

Autumn came late to the kingdom of Far Far Away. The harvest was exuberant and it is now time to get ready for the winter. As most people celebrate the Harvest festival, Simon the Caretaker tries to solve a very non-trivial task of how to find place for the agricultural equipment in the warehouse.

He's got problems with some particularly large piece of equipment, which is, of course, turboplows. The problem is that when a turboplow is stored, it takes up not some simply rectangular space. It takes up a T-shaped space like on one of the four pictures below (here character "\#" stands for the space occupied by the turboplow and character "." stands for the free space):

   `###      ..#      .#.      #..<br></br>.#.      ###      .#.      ###<br></br>.#.      ..#      ###      #..<br></br>`  Simon faced a quite natural challenge: placing in the given $ n×m $ cells warehouse the maximum number of turboplows. As one stores the turboplows, he can rotate them in any manner (so that they take up the space like on one of the four pictures above). However, two turboplows cannot "overlap", that is, they cannot share the same cell in the warehouse.

Simon feels that he alone cannot find the optimal way of positioning the plugs in the warehouse that would maximize their quantity. Can you help him?

## 样例 #1

### 输入

```
3 3
```

### 输出

```
1
AAA
.A.
.A.
```

## 样例 #2

### 输入

```
5 6
```

### 输出

```
4
A..C..
AAAC..
ABCCCD
.B.DDD
BBB..D
```

## 样例 #3

### 输入

```
2 2
```

### 输出

```
0
..
..
```

# 题解

## 作者：Acetyl (赞：11)

一看，就81个数据，那就打表吧。

先写一个直接dfs的程序，然后把程序的结果输出到一个文件里，再把这个文件里的东西复制到最终的程序中，就行了啊

dfs直接暴力不知道可不可以，但加一行剪枝就会快很多。

程序给出：

``` cpp
string dta[]={"0\n.\n","0\n..\n","0\n...\n","0\n....\n","0\n.....\n","0\n......\n","0\n.......\n","0\n........\n","0\n.........\n","0\n.\n.\n","0\n..\n..\n","0\n...\n...\n","0\n....\n....\n","0\n.....\n.....\n","0\n......\n......\n","0\n.......\n.......\n","0\n........\n........\n","0\n.........\n.........\n","0\n.\n.\n.\n","0\n..\n..\n..\n","1\nAAA\n.A.\n.A.\n","1\nAAA.\n.A..\n.A..\n","2\nAAA.B\n.ABBB\n.A..B\n","2\nAAABBB\n.A..B.\n.A..B.\n","3\nAAACBBB\n.A.C.B.\n.ACCCB.\n","3\nAAABBB.C\n.A..BCCC\n.A..B..C\n","4\nAAADBBB.C\n.A.D.BCCC\n.ADDDB..C\n","0\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n","1\nAAA\n.A.\n.A.\n...\n","2\nAAA.\n.AB.\n.AB.\n.BBB\n","2\nAAA..\n.ABBB\n.A.B.\n...B.\n","3\nAAABBB\n.AC.B.\n.AC.B.\n.CCC..\n","4\nAAABBB.\n.AC.BD.\n.AC.BD.\n.CCCDDD\n","4\nAAABBB..\n.AD.BCCC\n.AD.B.C.\n.DDD..C.\n","5\nAAABBBCCC\n.AD.BE.C.\n.AD.BE.C.\n.DDDEEE..\n","0\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n","2\nAAA\n.A.\nBA.\nBBB\nB..\n","2\nAAA.\n.A..\nBA..\nBBB.\nB...\n","4\nAAA.B\n.ABBB\nCA.DB\nCCCD.\nC.DDD\n","4\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC..D..\n","5\nAAABBB.\n.A..BD.\nCA.EBD.\nCCCEDDD\nC.EEE..\n","6\nAAABBB.C\n.A..BCCC\nDA.EB.FC\nDDDEEEF.\nD..E.FFF\n","7\nAAA.BBB.D\n.ACCCBDDD\nEA.CFB.GD\nEEECFFFG.\nE...F.GGG\n","0\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n","2\nAAA\n.A.\nBA.\nBBB\nB..\n...\n","3\nAAA.\n.A..\nBA..\nBBBC\nBCCC\n...C\n","4\nAAA..\n.ABBB\nCA.B.\nCCCBD\nC.DDD\n....D\n","5\nAAABBB\n.A..B.\n.AC.B.\n.ECCCD\n.ECDDD\nEEE..D\n","6\nAAA.BBB\n.AC..B.\n.ACCCB.\nE.CFDDD\nEEEF.D.\nE.FFFD.\n","7\nAAABBB..\n.AD.BCCC\n.AD.B.C.\nEDDDG.CF\nEEE.GFFF\nE..GGG.F\n","8\nAAABBBCCC\n.AD.B..C.\n.AD.BE.C.\nFDDDHEEEG\nFFF.HEGGG\nF..HHH..G\n","0\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n","3\nAAA\n.A.\nBA.\nBBB\nB.C\nCCC\n..C\n","4\nAAA.\n.AB.\n.AB.\nCBBB\nCCCD\nCDDD\n...D\n","5\nAAA..\n.ABBB\nCA.B.\nCCCB.\nCEDDD\n.E.D.\nEEED.\n","6\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nCE.DF.\n.EEEF.\n.E.FFF\n","8\nAAAC..B\n.A.CBBB\nDACCCEB\nDDDEEE.\nDHFFFEG\n.H.FGGG\nHHHF..G\n","9\nAAA.BBB.\n.ACCCBE.\n.ADC.BE.\nDDDCFEEE\nG.DIFFFH\nGGGIFHHH\nG.III..H\n","10\nAAA.BBB..\n.ACCCBDDD\n.AECFB.D.\nEEECFFFDG\nH.EJFIGGG\nHHHJ.IIIG\nH.JJJI...\n","0\n.\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n..\n","3\nAAA\n.A.\nBA.\nBBB\nB..\nCCC\n.C.\n.C.\n","4\nAAA.\n.A..\nBA..\nBBB.\nBCCC\n.DC.\n.DC.\nDDD.\n","6\nAAA..\n.ABBB\nCA.B.\nCCCBD\nC.DDD\nEEEFD\n.E.F.\n.EFFF\n","7\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC.ED..\n.GEEEF\n.GEFFF\nGGG..F\n","9\nAAA.BBB\n.ACCCB.\nDA.CEB.\nDDDCEEE\nDFFFE.G\n.IFHGGG\n.IFHHHG\nIIIH...\n","10\nAAABBB.C\n.A..BCCC\nDA.EB.FC\nDDDEEEF.\nD..EHFFF\nGGGJHHHI\n.G.JHIII\n.GJJJ..I\n","12\nAAA.BBB.D\n.ACCCBDDD\nEA.CFB.GD\nEEECFFFG.\nE..HFIGGG\nJHHHLIIIK\nJJJHLIKKK\nJ..LLL..K\n","0\n.\n.\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n..\n..\n","4\nAAA\n.A.\nBA.\nBBB\nB.C\nCCC\nD.C\nDDD\nD..\n","5\nAAA.\n.A..\nBA..\nBBBC\nBCCC\nD..C\nDDDE\nDEEE\n...E\n","7\nAAA..\n.ABBB\nCA.B.\nCCCBD\nCEDDD\n.EEED\nGEFFF\nGGGF.\nG..F.\n","8\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC.ED..\nEEEFFF\nG.EHF.\nGGGHF.\nG.HHH.\n","10\nAAABBB.\n.A..BD.\nCA.EBD.\nCCCEDDD\nCFEEE.G\n.FFFGGG\nIFHHHJG\nIIIH.J.\nI..HJJJ\n","12\nAAAC.BBB\n.ADCCCB.\n.ADCE.B.\nFDDDEEEG\nFFFHEGGG\nFHHHIIIG\nJJJHKIL.\n.JKKKIL.\n.J..KLLL\n","13\nAAABBB..C\n.A..BDCCC\nEA.GBDDDC\nEEEG.DFFF\nEHGGG.IF.\n.HHHIIIF.\nKHJJJMI.L\nKKKJ.MLLL\nK..JMMM.L\n"};
int n,m;

int main(){
	cin>>n>>m;
	cout<<dta[(n-1)*9+(m-1)]<<endl;
	return 0;
}
```

dfs的程序我就不给出了

---

## 作者：zgy_123 (赞：7)

[题目](https://www.luogu.com.cn/problem/CF142C)

[博客食用](https://www.luogu.com.cn/blog/GaViN2011/cf142c)

这是我的第一道紫，就写篇题解。

数据范围比较小，于是可以直接手打。

模板程序（生成程序框架）：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	for(int i=3;i<=9;i++){
		for(int j=3;j<=9;j++){
			cout<<"\tif(n=="<<i<<"&&m=="<<j<<"){\n";
			//'\t'相当于tab，'\n'相当于换行
			for(int x=0;x<=i;x++){
				cout<<"\t\tputs(\"";//'\"'双引号
                if(x!=0)
				    for(int y=1;y<=j;y++) cout<<'.';
				cout<<"\");\n";
			}
			cout<<"\t}\n";
		}
	} 
	return 0;
}
```
最后手填，代码较长，请勿抄袭：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	if(n<3||m<3){//一个T占3*3
		cout<<0<<endl;
		for(int i=1;i<=n;i++,cout<<endl)
			for(int j=1;j<=m;j++) cout<<'.';
	}
	if(n==3&&m==3){//大模拟
		puts("1");//puts自带换行
		puts("AAA");
		puts(".A.");
		puts(".A.");
	}
	if(n==3&&m==4){
		puts("1");
		puts("AAA.");
		puts(".A..");
		puts(".A..");
	}
	if(n==3&&m==5){
		puts("2");
		puts("AAAB.");
		puts(".A.B.");
		puts(".ABBB");
	}
	if(n==3&&m==6){
		puts("2");
		puts("AAAB..");
		puts(".A.B..");
		puts(".ABBB.");
	}
	if(n==3&&m==7){
		puts("3");
		puts("AAABCCC");
		puts(".A.B.C.");
		puts(".ABBBC.");
	}
	if(n==3&&m==8){
		puts("3");
		puts("AAABCCC.");
		puts(".A.B.C..");
		puts(".ABBBC..");
	}
	if(n==3&&m==9){
		puts("4");
		puts("AAABCCCD.");
		puts(".A.B.C.D.");
		puts(".ABBBCDDD");
	}
	if(n==4&&m==3){
		puts("1");
		puts("AAA");
		puts(".A.");
		puts(".A.");
		puts("...");
	}
	if(n==4&&m==4){
		puts("2");
		puts("AAA.");
		puts(".AB.");
		puts(".AB.");
		puts(".BBB");
	}
	if(n==4&&m==5){
		puts("2");
		puts("AAA..");
		puts(".ABBB");
		puts(".A.B.");
		puts("...B.");
	}
	if(n==4&&m==6){
		puts("3");
		puts("AAA...");
		puts(".AB..C");
		puts(".ABCCC");
		puts(".BBB.C");
	}
	if(n==4&&m==7){
		puts("4");
		puts("AAACCC.");
		puts(".AB.CD.");
		puts(".AB.CD.");
		puts(".BBBDDD");
	}
	if(n==4&&m==8){
		puts("4");
		puts("AAACCC..");
		puts(".AB.CD..");
		puts(".AB.CD..");
		puts(".BBBDDD.");
	}
	if(n==4&&m==9){
		puts("5");
		puts("AAACCCDDD");
		puts(".AB.CE.D.");
		puts(".AB.CE.D.");
		puts(".BBBEEE..");
	}
	if(n==5&&m==3){
		puts("2");
		puts("AAA");
		puts(".A.");
		puts("BA.");
		puts("BBB");
		puts("B..");
	}
	if(n==5&&m==4){
		puts("2");
		puts("AAA.");
		puts(".AB.");
		puts(".AB.");
		puts(".BBB");
		puts("....");
	}
	if(n==5&&m==5){
		puts("4");
		puts("AAA.B");
		puts(".ABBB");
		puts("CA.DB");
		puts("CCCD.");
		puts("C.DDD");
	}
	if(n==5&&m==6){
		puts("4");
		puts("AAABBB");
		puts(".A..B.");
		puts("CA..BD");
		puts("CCCDDD");
		puts("C....D");
	}
	if(n==5&&m==7){
		puts("5");
		puts("AAABCCC");
		puts(".A.B.C.");
		puts("DABBBCE");
		puts("DDD.EEE");
		puts("D.....E");
	}
	if(n==5&&m==8){
		puts("6");
		puts("AAABBB.C");
		puts(".A..BCCC");
		puts("DA.FB.EC");
		puts("DDDFFFE.");
		puts("D..F.EEE");
	}
	if(n==5&&m==9){
		puts("7");
		puts("GGG.CCC.E");
		puts(".GAAACEEE");
		puts(".GBADC.FE");
		puts("..BADDDF.");
		puts(".BBBD.FFF");
	}
	if(n==6&&m==3){
		puts("2");
		puts("AAA");
		puts(".A.");
		puts(".A.");
		puts("BBB");
		puts(".B.");
		puts(".B.");
	}
	if(n==6&&m==4){
		puts("3");
		puts("AAA.");
		puts(".A..");
		puts(".A.C");
		puts("BCCC");
		puts("BBBC");
		puts("B...");
	}
	if(n==6&&m==5){
		puts("4");
		puts("AAA.B");
		puts(".ABBB");
		puts("CA.DB");
		puts("CCCD.");
		puts("C.DDD");
		puts(".....");
	}
	if(n==6&&m==6){
		puts("5");
		puts("AAABBB");
		puts(".AC.B.");
		puts(".AC.B.");
		puts("DCCC.E");
		puts("DDDEEE");
		puts("D....E");
	}
	if(n==6&&m==7){
		puts("6");
		puts("AAACBBB");
		puts(".A.C.B.");
		puts("DACCCBE");
		puts("DDDFEEE");
		puts("D..F..E");
		puts("..FFF..");
	}
	if(n==6&&m==8){
		puts("7");
		puts("AAABCCC.");
		puts(".A.B.C..");
		puts("DABBBC.G");
		puts("DDDEFGGG");
		puts("DEEEFFFG");
		puts("...EF...");
	}
	if(n==6&&m==9){
		puts("8");
		puts("AAAEBBB.C");
		puts(".A.E.BCCC");
		puts("FAEEEBG.C");
		puts("FFFHGGGD.");
		puts("F..H..GD.");
		puts("..HHH.DDD");
	}
	if(n==7&&m==3){
		puts("3");
		puts("AAA");
		puts(".A.");
		puts("BA.");
		puts("BBB");
		puts("BC.");
		puts(".C.");
		puts("CCC");
	}
	if(n==7&&m==4){
		puts("4");
		puts("A...");
		puts("AAAB");
		puts("ABBB");
		puts("CCCB");
		puts(".CD.");
		puts(".CD.");
		puts(".DDD");
	}
	if(n==7&&m==5){
		puts("5");
		puts("AAA.B");
		puts(".ABBB");
		puts("CA.DB");
		puts("CCCD.");
		puts("CEDDD");
		puts(".E...");
		puts("EEE..");
	}
	if(n==7&&m==6){
		puts("6");
		puts("AAABBB");
		puts(".A..B.");
		puts("DA..BC");
		puts("DDDCCC");
		puts("DE..FC");
		puts(".E..F.");
		puts("EEEFFF");
	}
	if(n==7&&m==7){
		puts("8");
		puts("A.BBB.C");
		puts("AAABCCC");
		puts("A.EBH.C");
		puts("EEE.HHH");
		puts("F.EDH.G");
		puts("FFFDGGG");
		puts("F.DDD.G");
	}
	if(n==7&&m==8){
		puts("9");
		puts("A.BBB..D");
		puts("AAABCDDD");
		puts("A.GBCCCD");
		puts("GGGHCEEE");
		puts(".IGH.FE.");
		puts(".IHHHFE.");
		puts("III.FFF.");
	}
	if(n==7&&m==9){
		puts("10");
		puts("A..DFFF.H");
		puts("AAAD.FHHH");
		puts("ACDDDFI.H");
		puts(".C.EEEIII");
		puts("CCCBEGI.J");
		puts(".BBBEGJJJ");
		puts("...BGGG.J");
	}
	if(n==8&&m==3){
		puts("3");
		puts("AAA");
		puts(".A.");
		puts(".A.");
		puts("BBB");
		puts(".B.");
		puts("CB.");
		puts("CCC");
		puts("C..");
	}
	if(n==8&&m==4){
		puts("4");
		puts("AAA.");
		puts(".AB.");
		puts(".AB.");
		puts("CBBB");
		puts("CCCD");
		puts("CDDD");
		puts("...D");
		puts("....");
	}
	if(n==8&&m==5){
		puts("6");
		puts("AAA.B");
		puts(".ABBB");
		puts("CA.DB");
		puts("CCCD.");
		puts("CEDDD");
		puts(".EEEF");
		puts(".EFFF");
		puts("....F");
	}
	if(n==8&&m==6){
		puts("7");
		puts("AAABBB");
		puts(".AD.B.");
		puts(".AD.B.");
		puts("EDDD.C");
		puts("EEECCC");
		puts("EF..GC");
		puts(".F..G.");
		puts("FFFGGG");
	}
	if(n==8&&m==7){
		puts("9");
		puts("AAAB..C");
		puts(".A.BCCC");
		puts("DABBBFC");
		puts("DDDFFF.");
		puts("DEEE.FI");
		puts(".HEGIII");
		puts(".HEGGGI");
		puts("HHHG...");
	}
	if(n==8&&m==8){
		puts("10");
		puts("AAA.BCCC");
		puts(".ABBBFC.");
		puts("EA.DBFC.");
		puts("EEEDFFFG");
		puts("EHDDDGGG");
		puts(".HIII.JG");
		puts("HHHIJJJ.");
		puts("...I..J.");
	}
	if(n==8&&m==9){
		puts("12");
		puts("A.EEE.JJJ");
		puts("AAAEHHHJ.");
		puts("AB.EFHKJ.");
		puts(".BFFFHKKK");
		puts("BBBDFGK..");
		puts("CDDDIGGGL");
		puts("CCCDIGLLL");
		puts("C..III..L");
	}
	if(n==9&&m==3){
		puts("4");
		puts("AAA");
		puts(".A.");
		puts("BA.");
		puts("BBB");
		puts("B.C");
		puts("CCC");
		puts(".DC");
		puts(".D.");
		puts("DDD");
	}
	if(n==9&&m==4){
		puts("5");
		puts("AAA.");
		puts(".AB.");
		puts(".AB.");
		puts("CBBB");
		puts("CCCD");
		puts("CDDD");
		puts("..ED");
		puts("..E.");
		puts(".EEE");
	}
	if(n==9&&m==5){
		puts("7");
		puts("AAA.B");
		puts(".ABBB");
		puts("CA.DB");
		puts("CCCD.");
		puts("CEDDD");
		puts(".EEEF");
		puts("GEFFF");
		puts("GGG.F");
		puts("G....");
	}
	if(n==9&&m==6){
		puts("8");
		puts("AAABBB");
		puts(".AC.B.");
		puts(".AC.B.");
		puts("ECCC.D");
		puts("EEEDDD");
		puts("E.GGGD");
		puts("HHHGF.");
		puts(".H.GF.");
		puts(".H.FFF");
	}
	if(n==9&&m==7){
		puts("10");
		puts("AAA.B..");
		puts(".ABBBC.");
		puts("DA.EBC.");
		puts("DDDECCC");
		puts("DFEEE.G");
		puts(".FFFGGG");
		puts("HFIIIJG");
		puts("HHHI.J.");
		puts("H..IJJJ");
	}
	if(n==9&&m==8){
		puts("12");
		puts("AAA.BCCC");
		puts(".ABBBFC.");
		puts("DA.EBFC.");
		puts("DDDEFFFG");
		puts("DHEEEGGG");
		puts(".HHHIIIG");
		puts("KHLLLIJ.");
		puts("KKKL.IJ.");
		puts("K..L.JJJ");
	}
	if(n==9&&m==9){
		puts("13");
		puts("AAA.BCCC.");
		puts(".ABBB.CD.");
		puts(".AE.BFCD.");
		puts("EEEFFFDDD");
		puts("M.E.GFHHH");
		puts("MMMLGGGH.");
		puts("MK.LGJ.HI");
		puts(".KLLLJIII");
		puts("KKK.JJJ.I");
	}
	return 0;
}
```

---

## 作者：LightningUZ (赞：6)

很显然暴搜会超时，所以要状压dp。

dp(i,j,mask)表示考虑到前i-1行的全部和第i行的前j个，每种状态只和前3行有关，所以mask表示前3行的填充状态。转移时，枚举“T”的方向，算出新mask即可,记忆化搜索。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;
typedef pair<pair<int,int>,int> mpair;
const char figure[4][3][3]=
{
	{
		{'#','#','#'},
		{'.','#','.'},
		{'.','#','.'}
	},
	{
		{'.','#','.'},
		{'.','#','.'},
		{'#','#','#'}
	},
	{
		{'.','.','#'},
		{'#','#','#'},
		{'.','.','#'}
	},
	{
		{'#','.','.'},
		{'#','#','#'},
		{'#','.','.'}
	}
};
int a[N][N];
int n,m;
map<mpair,int>mp;
int rec(int x,int y,int mask)
{
	if(m<y)
		return rec(x+1,1,mask);
	if(n<x+2)
		return 0;
	mpair p=make_pair(make_pair(x,y),mask);
	if(mp.find(p)!=mp.end())
		return mp[p];
	int &res=mp[p]=0;
	res=rec(x,y+1,mask>>1);
	if(y+2<=m)
	{
		for(int k=0;k<4;k++)
		{
			bool flag=true;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						flag&=(mask&(1<<(i*m+j)))==0;
			if(!flag)
				continue;
			int nmask=mask;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						nmask|=1<<(i*m+j);
			res=max(res,rec(x,y+1,nmask>>1)+1);
		}
	}
	return res;
}
int recovery(int x,int y,int mask,int res)
{
	if(res==0)
		return 0;
	if(m<y)
		return recovery(x+1,1,mask,res);
	if(n<x+2)
		return 0;
	if(res==rec(x,y+1,mask>>1))
	{
		recovery(x,y+1,mask>>1,res);
		return 0;	
	} 
	if(y+2<=m)
	{
		for(int k=0;k<4;k++)
		{
			bool flag=true;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						flag&=(mask&(1<<(i*m+j)))==0;
			if(!flag)
				continue;
			int nmask=mask;
			for(int i=0;i<3;i++)	
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						nmask|=(1<<(i*m+j));
			if(res==rec(x,y+1,nmask>>1)+1)
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						if(figure[k][i][j]=='#')
							a[x+i][y+j]=res;
				recovery(x,y+1,nmask>>1,res-1);
				return 0;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	int ans=rec(1,1,0);
	printf("%d\n",ans);
	recovery(1,1,0,ans);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%c",a[i][j]?'A'+a[i][j]-1:'.');
		printf("\n");
	}
	return 0;
}

```



~~（我是蒟蒻，不会状压）~~

其实这道题搜索也可以过，不过要加上最优化剪枝。如果剩下的所有没考虑的空格数/5加上现在的个数小于等于目前已有的答案，则直接跳过。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;
typedef pair<pair<int,int>,int> mpair;
const char figure[4][3][3]=
{
	{
		{'#','#','#'},
		{'.','#','.'},
		{'.','#','.'}
	},
	{
		{'.','#','.'},
		{'.','#','.'},
		{'#','#','#'}
	},
	{
		{'.','.','#'},
		{'#','#','#'},
		{'.','.','#'}
	},
	{
		{'#','.','.'},
		{'#','#','#'},
		{'#','.','.'}
	}
};
int a[N][N];
int n,m;
map<mpair,int>mp;
int rec(int x,int y,int mask)
{
	if(m<y)
		return rec(x+1,1,mask);
	if(n<x+2)
		return 0;
	mpair p=make_pair(make_pair(x,y),mask);
	if(mp.find(p)!=mp.end())
		return mp[p];
	int &res=mp[p]=0;
	res=rec(x,y+1,mask>>1);
	if(y+2<=m)
	{
		for(int k=0;k<4;k++)
		{
			bool flag=true;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						flag&=(mask&(1<<(i*m+j)))==0;
			if(!flag)
				continue;
			int nmask=mask;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						nmask|=1<<(i*m+j);
			res=max(res,rec(x,y+1,nmask>>1)+1);
		}
	}
	return res;
}
int recovery(int x,int y,int mask,int res)
{
	if(res==0)
		return 0;
	if(m<y)
		return recovery(x+1,1,mask,res);
	if(n<x+2)
		return 0;
	if(res==rec(x,y+1,mask>>1))
	{
		recovery(x,y+1,mask>>1,res);
		return 0;	
	} 
	if(y+2<=m)
	{
		for(int k=0;k<4;k++)
		{
			bool flag=true;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						flag&=(mask&(1<<(i*m+j)))==0;
			if(!flag)
				continue;
			int nmask=mask;
			for(int i=0;i<3;i++)	
				for(int j=0;j<3;j++)
					if(figure[k][i][j]=='#')
						nmask|=(1<<(i*m+j));
			if(res==rec(x,y+1,nmask>>1)+1)
			{
				for(int i=0;i<3;i++)
					for(int j=0;j<3;j++)
						if(figure[k][i][j]=='#')
							a[x+i][y+j]=res;
				recovery(x,y+1,nmask>>1,res-1);
				return 0;
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	int ans=rec(1,1,0);
	printf("%d\n",ans);
	recovery(1,1,0,ans);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			printf("%c",a[i][j]?'A'+a[i][j]-1:'.');
		printf("\n");
	}
	return 0;
}

```


---

## 作者：jinhangdong (赞：4)

这道题目不算难，只需要稍微的剪枝就可以。

机器的摆放只有 4 种方式，所以我们可以枚举这 4 种方式就可以了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11][11],b[11][11],xa,ya,n,m,t;
char c[11][11];
void dfs(int x,int y,int s)
{
	if(x==n)//如果遍历到了最后一行 
	{
		if(s>t)
		{
			t=s;//求最多可以放多少个机器 
			for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			if(a[i][j]==0) c[i][j]='.';
			else c[i][j]=a[i][j];
			//存储机器摆放的样子 
		}
		return;
	}
	if(!a[x][y]&&!a[x-1][y-1]&&!a[x-1][y]&&!a[x-1][y+1]&&!a[x+1][y])//判断能否放置机器 
	{
		a[x][y]=s+65;
		a[x-1][y-1]=s+65;
		a[x-1][y]=s+65;
		a[x-1][y+1]=s+65;
		a[x+1][y]=s+65;
		//标记 
		if(s+1>=b[x][y])//如果放好这个不少于到这个位置最多可以放多少个 
		{
			if(y==m-1) dfs(x+1,2,s+1);//如果到了最后一个可放置机器的位置那就换行 
			else dfs(x,y+1,s+1);//换个位置 
		}
		a[x][y]=0;
		a[x-1][y-1]=0;
		a[x-1][y]=0;
		a[x-1][y+1]=0;
		a[x+1][y]=0;
		//去除标记 
		b[x][y]=max(b[x][y],s);//记录到这个位置最多可以放多少个 
	}
	if(!a[x][y]&&!a[x][y-1]&&!a[x][y+1]&&!a[x-1][y+1]&&!a[x+1][y+1])//把机器旋转继续判断 
	{
		a[x][y]=s+65;
		a[x][y-1]=s+65;
		a[x][y+1]=s+65;
		a[x-1][y+1]=s+65;
		a[x+1][y+1]=s+65;
		if(s+1>=b[x][y])
		{
			if(y==m-1) dfs(x+1,2,s+1);
			else dfs(x,y+1,s+1);
		}
		a[x][y]=0;
		a[x][y-1]=0;
		a[x][y+1]=0;
		a[x-1][y+1]=0;
		a[x+1][y+1]=0;
		b[x][y]=max(b[x][y],s);
	}
	if(!a[x][y]&&!a[x-1][y]&&!a[x+1][y-1]&&!a[x+1][y]&&!a[x+1][y+1])//把机器旋转继续判断 
	{
		a[x][y]=s+65;
		a[x-1][y]=s+65;
		a[x+1][y-1]=s+65;
		a[x+1][y]=s+65;
		a[x+1][y+1]=s+65;
		if(s+1>=b[x][y])
		{
			if(y==m-1) dfs(x+1,2,s+1);
			else dfs(x,y+1,s+1);
		}
		a[x][y]=0;
		a[x-1][y]=0;
		a[x+1][y-1]=0;
		a[x+1][y]=0;
		a[x+1][y+1]=0;
		b[x][y]=max(b[x][y],s);
	}
	if(!a[x][y]&&!a[x-1][y-1]&&!a[x][y-1]&&!a[x][y+1]&&!a[x+1][y-1])//把机器旋转继续判断 
	{
		a[x][y]=s+65;
		a[x-1][y-1]=s+65;
		a[x][y-1]=s+65;
		a[x][y+1]=s+65;
		a[x+1][y-1]=s+65;
		if(s+1>=b[x][y])
		{
			if(y==m-1) dfs(x+1,2,s+1);
			else dfs(x,y+1,s+1);
		}
		a[x][y]=0;
		a[x-1][y-1]=0;
		a[x][y-1]=0;
		a[x][y+1]=0;
		a[x+1][y-1]=0;
		b[x][y]=max(b[x][y],s);
	}
	//是否可以摆放
	if(y==m-1) dfs(x+1,2,s);
	else dfs(x,y+1,s);
}
int main()
{
	cin>>n>>m;
	if(n<3||m<3)//特判不加也可以  
	{
		cout<<0<<endl;
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j) cout<<".";
			cout<<endl;
		}
		return 0;
	}
	dfs(2,2,0);//进行深度优先搜索 
	cout<<t<<endl;//输出最多可以放几个机器 
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j) cout<<char(c[i][j]);
		cout<<endl;
	}
	//输出机器摆放的样子
	return 0;
}
```


---

## 作者：流水行船CCD (赞：4)

# 思路

因为这道题数据较小，且只有 $81$ 种 情况，考虑爆搜。

~~实在过不了，也可以本地打表~~。

爆搜这题看似很难，但其实我们可以对一台机器用一个点进行表示：

给出一个 T 字向下的模型。

![](https://cdn.luogu.com.cn/upload/image_hosting/w3qczr3r.png)

因此，我们将这个 T 字进行旋转，一共四个方向，就可以得到一个二维数组，因此我们就可以通过枚举 T 字中间的那一个点，即途中标红的点和 T 字的朝向，从而算出这个 T 字每一个点所对应的坐标。

这样我们就不用使用庞杂的分类讨论，而通过使用循环大大减少代码量！

接下来思考枚举顺序。

由于每一个点都可能作为 T 字机器的枚举点，因此我们可以从左往右，从上往下依次 DP，注意一定不要像普通 DFS 那样去枚举当前点周围的点，否则会出现一些地方本来可以放 T 字而程序却枚举不到的情况。

枚举顺序如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ucih7gye.png)

然后就 TLE 了最后 6 个点。

所以我们只需要把 $7 \le n,m$ 的情况离线出来就可以了。

# AC Code

## 提交代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace DFS{
	int n,m;
	int dx[4][4]={{0,0,-1,-2},{1,-1,0,0},{0,0,1,2},{-1,1,0,0}};
	int dy[4][4]={{-1,1,0,0},{0,0,-1,-2},{1,-1,0,0},{0,0,1,2}};
	int ans=0;
	char Ans[15][15],realAns[15][15];
	bool vis[15][15];
	void dfs(int ux,int uy,int cnt){
		//cout<<ux<<" "<<uy<<" "<<cnt<<endl;
		if(ux>n||ux<1||uy>m||uy<1){return;}
		if(ux==n&&uy==m){
			if(ans<cnt){
				ans=cnt;
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						realAns[i][j]=Ans[i][j];
					}
				}
				return;
			}
			return;
		}
		if(ux<n){dfs(ux+1,uy,cnt);}
		else{dfs(1,uy+1,cnt);}
		if(vis[ux][uy]){return;}
		for(int fx=0;fx<4;fx++){
			bool flag=1;
			for(int i=0;i<4;i++){
				int nowx=ux+dx[fx][i];
				int nowy=uy+dy[fx][i];
				if(!(1<=nowx&&nowx<=n&&1<=nowy&&nowy<=m)){flag=0;break;}
				if(vis[nowx][nowy]){flag=0;break;}
			}
			if(!flag){continue;}
			//cout<<ux<<" "<<uy<<" "<<cnt<<endl;
			for(int i=0;i<4;i++){
				int nowx=ux+dx[fx][i];
				int nowy=uy+dy[fx][i];
				vis[nowx][nowy]=1;
				Ans[nowx][nowy]=char(cnt+'A');
			}
			Ans[ux][uy]=char(cnt+'A');
			vis[ux][uy]=1;
			if(ux<n){dfs(ux+1,uy,cnt+1);}
			else{dfs(1,uy+1,cnt+1);}
			vis[ux][uy]=0;
			Ans[ux][uy]='.';
			for(int i=0;i<4;i++){
				int nowx=ux+dx[fx][i];
				int nowy=uy+dy[fx][i];
				vis[nowx][nowy]=0;
				Ans[nowx][nowy]='.';
			}
		}
		return;
	}
	signed main(){
		scanf("%d%d",&n,&m);
		if(n==7&&m==7){
		printf("8\n");
		printf("BBB.GGG\n");
		
		printf(".BDDDG.\n");
		
		printf(".BCDFG.\n");
		
		printf("CCCDFFF\n");
		
		printf("A.CEF.H\n");
		
		printf("AAAEHHH\n");
		
		printf("A.EEE.H\n");
		return 0;
		}
		
		if(n==7&&m==8){
		printf("9\n");
		printf(".CCCE..H\n");
		
		printf(".BC.EHHH\n");
		
		printf(".BCEEEGH\n");
		
		printf("BBBDGGG.\n");
		
		printf("ADDDF.GI\n");
		
		printf("AAADFIII\n");
		
		printf("A..FFF.I\n");
		return 0;
		}
		
		if(n==7&&m==9){
		printf("10\n");
		printf(".CCCFFF.I\n");
		
		printf(".AC.EFIII\n");
		
		printf(".AC.EFH.I\n");
		
		printf("AAAEEEHHH\n");
		
		printf(".BDDDGH.J\n");
		
		printf(".B.D.GJJJ\n");
		
		printf("BBBDGGG.J\n");
		return 0;
		}
		
		if(n==8&&m==7){
		printf("9\n");
		printf("BBB.GGG\n");
		
		printf(".BDDDG.\n");
		
		printf(".BCD.GI\n");
		
		printf("CCCDIII\n");
		
		printf("A.CFFFI\n");
		
		printf("AAAEFH.\n");
		
		printf("AEEEFH.\n");
		
		printf("...EHHH\n");
		return 0;
		}
		
		if(n==8&&m==8){
		printf("10\n");
		printf("..C.EHHH\n");
		
		printf("CCC.E.H.\n");
		
		printf(".ACEEEHJ\n");
		
		printf(".ADDDJJJ\n");
		
		printf("AAADGGGJ\n");
		
		printf(".B.DFGI.\n");
		
		printf(".BFFFGI.\n");
		
		printf("BBB.FIII\n");
		return 0;
		}
		
		if(n==8&&m==9){
		printf("12\n");
		printf("..CFFF..K\n");
		
		printf("CCCDFHKKK\n");
		
		printf(".BCDFHHHK\n");
		
		printf(".BDDDHJJJ\n");
		
		printf("BBBEIIIJ.\n");
		
		printf("AEEEGI.JL\n");
		
		printf("AAAEGILLL\n");
		
		printf("A..GGG..L\n");
		return 0;
		}
		
		if(n==9&&m==7){
		printf("10\n");
		printf(".DDD..I\n");
		
		printf(".BDEIII\n");
		
		printf(".BDEEEI\n");
		
		printf("BBBEHHH\n");
		
		printf("CCC.GH.\n");
		
		printf(".CGGGH.\n");
		
		printf("AC.FG.J\n");
		
		printf("AAAFJJJ\n");
		
		printf("A.FFF.J\n");
		return 0;
		}
		
		if(n==9&&m==8){
		printf("12\n");
		printf(".DDDGJJJ\n");
		
		printf(".BD.G.J.\n");
		
		printf(".BDGGGJL\n");
		
		printf("BBBEHLLL\n");
		
		printf("AEEEHHHL\n");
		
		printf("AAAEHKKK\n");
		
		printf("ACFFFIK.\n");
		
		printf(".C.F.IK.\n");
		
		printf("CCCFIII.\n");
		return 0;
		}
		
		if(n==9&&m==9){
		printf("13\n");
		printf("..CFFFKKK\n");
		
		printf("CCCEF.IK.\n");
		
		printf(".ACEF.IK.\n");
		
		printf(".AEEEIIIM\n");
		
		printf("AAAGGGMMM\n");
		
		printf(".DDDGJJJM\n");
		
		printf(".BD.GHJL.\n");
		
		printf(".BDHHHJL.\n");
		
		printf("BBB..HLLL\n");
		return 0;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				Ans[i][j]='.';
				realAns[i][j]='.';
			}
		}
		dfs(1,1,0);
		printf("%d\n",ans);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				putchar(realAns[i][j]);
			}
			putchar('\n');
		}
		return 0;
	}
}
signed main(){
	DFS::main();
	return 0;
}

```


## 打表代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace DFS{
	int n,m;
	int dx[4][4]={{0,0,-1,-2},{1,-1,0,0},{0,0,1,2},{-1,1,0,0}};
	int dy[4][4]={{-1,1,0,0},{0,0,-1,-2},{1,-1,0,0},{0,0,1,2}};
	int ans=0;
	int Maxcnt[15][15];
	char Ans[15][15],realAns[15][15];
	bool vis[15][15];
	void dfs(int ux,int uy,int cnt){
		//cout<<ux<<" "<<uy<<" "<<cnt<<endl;
		if(ux>n||ux<1||uy>m||uy<1){return;}
		if(ux==n&&uy==m){
			if(ans<cnt){
				ans=cnt;
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						realAns[i][j]=Ans[i][j];
					}
				}
				return;
			}
			return;
		}
		if(cnt+2<Maxcnt[ux][uy]){return;}
		Maxcnt[ux][uy]=max(Maxcnt[ux][uy],cnt); 
		if(ux<n){dfs(ux+1,uy,cnt);}
		else{dfs(1,uy+1,cnt);}
		if(vis[ux][uy]){return;}
		for(int fx=0;fx<4;fx++){
			bool flag=1;
			for(int i=0;i<4;i++){
				int nowx=ux+dx[fx][i];
				int nowy=uy+dy[fx][i];
				if(!(1<=nowx&&nowx<=n&&1<=nowy&&nowy<=m)){flag=0;break;}
				if(vis[nowx][nowy]){flag=0;break;}
			}
			if(!flag){continue;}
			//cout<<ux<<" "<<uy<<" "<<cnt<<endl;
			for(int i=0;i<4;i++){
				int nowx=ux+dx[fx][i];
				int nowy=uy+dy[fx][i];
				vis[nowx][nowy]=1;
				Ans[nowx][nowy]=char(cnt+'A');
			}
			Ans[ux][uy]=char(cnt+'A');
			vis[ux][uy]=1;
			if(ux<n){dfs(ux+1,uy,cnt+1);}
			else{dfs(1,uy+1,cnt+1);}
			vis[ux][uy]=0;
			Ans[ux][uy]='.';
			for(int i=0;i<4;i++){
				int nowx=ux+dx[fx][i];
				int nowy=uy+dy[fx][i];
				vis[nowx][nowy]=0;
				Ans[nowx][nowy]='.';
			}
		}
		return;
	}
	signed main(){
		for(n=7;n<=9;n++){
			for(m=7;m<=9;m++){
				ans=0;
				printf("if(n==%d&&m==%d){\n",n,m);
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						Ans[i][j]='.';
						realAns[i][j]='.';
						vis[i][j]=0;
						Maxcnt[i][j]=0;
					}
				}
				dfs(1,1,0);
				printf("printf(\"%d\\n\");\n",ans);
				for(int i=1;i<=n;i++){
					printf("printf(\"");
					for(int j=1;j<=m;j++){
						putchar(realAns[i][j]);
					}
					printf("\\n\");\n");
					putchar('\n');
				}
				printf("}\n");
				printf("\n");
			}
		}
		
		return 0;
	}
}
signed main(){
	DFS::main();
	return 0;
}
```

---

## 作者：liruixiong0101 (赞：4)

## 题意简述
在一个 $n\times m$ 的一个矩阵中，你可以放任意个形如 T 的机器只要不超出范围。  
机器的形状如下：
```cpp
AAA   A   A   A
 A  AAA   A   AAA
 A    A  AAA  A
```

## 思路
首先我们可以枚举每一个空地，看看能不能放下这 4 种 T 能放下的就放然后回溯放另一个，一直放等放不了了就选放的最多的那一种情况，即可（就是爆搜但需要一点点技巧）。

------------

代码如下 ~~（代码是不是来的太快了一点点）~~：
```cpp
#include <bits/stdc++.h>
#define re register
#define il inline//卡常不卡会多T两个点
using namespace std;
const int N = 15;
const int dx[4][4] = {{0 , 0 , -1 , 1} ,
                      {0 , 0 , 1 , 2} ,
                      {-1 , 1 , 0 , 0} ,
                      {-2 , -1 , 0 , 0}};
const int dy[4][4] = {{-2 , -1 , 0 , 0} ,
                      {-1 , 1 , 0 , 0} ,
                      {0 , 0 , 1 , 2} ,
                      {0 , 0 , -1 , 1}};
//dx，dy数组一会儿会解释
int n , m , ans = -1 , anss[N][N];
int a[N][N];
il bool pd1(int x , int y){
	if(x < 1 || y < 1) return 0;
	if(x > n || y > m) return 0;
	return 1;
}//判断x，y是否在矩形内
il bool pd2(int x , int y){
	return !a[x][y];
}//判断a[x][y]是不是没放东西
il bool PD(int x , int y , int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , int x4 , int y4){
	return pd1(x , y) && pd1(x1 , y1) && pd1(x2 , y2) && pd1(x3 , y3) && pd1(x4 , y4) && pd2(x , y) && pd2(x1 , y1) && pd2(x2 , y2) && pd2(x3 , y3) && pd2(x4 , y4);
}//看看能不能放这个T
void dfs(int x , int y , int cnt){
    if(ans == n * m / 5) return;//剪枝
	if(x == n && y == m){
        int num = 0;
        bool flag = 0;
		for(re int i = 0; i < 4; i++){
            int nx1 = x + dx[i][0] , ny1 = y + dy[i][0];
            int nx2 = x + dx[i][1] , ny2 = y + dy[i][1];
            int nx3 = x + dx[i][2] , ny3 = y + dy[i][2];
            int nx4 = x + dx[i][3] , ny4 = y + dy[i][3];
            if(PD(x , y , nx1 , ny1 , nx2 , ny2 , nx3 , ny3 , nx4 , ny4)){
                num++ , flag = 1;
                a[x][y] = a[nx1][ny1] = a[nx2][ny2] = cnt + num;
                break;
            }
        }
        //找到最后一个T
        if(ans < cnt + num){
            ans = cnt + num;
            memcpy(anss , a , sizeof(a));
        }
		return;
	}
	int num = 0;
	bool flag = 0;
	for(re int i = 0; i < 4; i++){
		int nx1 = x + dx[i][0] , ny1 = y + dy[i][0];
		int nx2 = x + dx[i][1] , ny2 = y + dy[i][1];
        int nx3 = x + dx[i][2] , ny3 = y + dy[i][2];
        int nx4 = x + dx[i][3] , ny4 = y + dy[i][3];
		if(PD(x , y , nx1 , ny1 , nx2 , ny2 , nx3 , ny3 , nx4 , ny4)){
			num++;
			a[x][y] = a[nx1][ny1] = a[nx2][ny2] = a[nx3][ny3] = a[nx4][ny4] = cnt + num;
			dfs(((y + 1 > m) ? x + 1 : x) , ((y + 1 > m) ? 1 : y + 1) , cnt + 1);
			a[x][y] = a[nx1][ny1] = a[nx2][ny2] = a[nx3][ny3] = a[nx4][ny4] = 0;
            num--;
            //放T
		}
	}
	dfs(((y + 1 > m) ? x + 1 : x) , ((y + 1 > m) ? 1 : y + 1) , cnt);
	//不放T
}
int main(){
    scanf("%d%d" , &n , &m);
    dfs(1 , 1 , 0);
    printf("%d\n" , ans);
    for(re int i = 1; i <= n; i++){
        for(re int j = 1; j <= m; j++){
            if(!anss[i][j]) printf(".");
            else printf("%c" , (char)(anss[i][j] + 'A' - 1));
        }
        printf("\n");
    }//输出
	return 0;
}
```
以上代码的 dx，dy 数组分别表示每一种 T 摆放位置的每一个点距离原点的 x，y 轴距离。
![](https://cdn.luogu.com.cn/upload/image_hosting/cjuflq1d.png)
由此，我们可以推出机器摆放方式为如下的 dx，dy：
```
       ②
0--O ① O--原点
       ③
```
```cpp
dx[0][0] = 0 , dy[0][0] = -2;
dx[0][1] = 0 , dy[0][1] = -1;
dx[0][2] = -1 , dy[0][2] = 0;
dx[0][3] = 1 , dy[0][3] = 0;
```

------------
<https://codeforces.com/problemset/submission/142/197211379>

然后我们就得到了 TLE 的~~好~~成绩。
由于我懒还是打表算了。~~也就打 6 个表而已嘛。~~

### AC CODE:
```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
using namespace std;
const int N = 15;
const int dx[4][4] = {{0 , 0 , -1 , 1} ,
                      {0 , 0 , 1 , 2} ,
                      {-1 , 1 , 0 , 0} ,
                      {-2 , -1 , 0 , 0}};
const int dy[4][4] = {{-2 , -1 , 0 , 0} ,
                      {-1 , 1 , 0 , 0} ,
                      {0 , 0 , 1 , 2} ,
                      {0 , 0 , -1 , 1}};
int n , m , ans = -1 , anss[N][N];
int a[N][N];
il bool pd1(int x , int y){
	if(x < 1 || y < 1) return 0;
	if(x > n || y > m) return 0;
	return 1;
}
il bool pd2(int x , int y){
	return !a[x][y];
}
il bool PD(int x , int y , int x1 , int y1 , int x2 , int y2 , 
int x3 , int y3 , int x4 , int y4){
    return pd1(x , y) && pd1(x1 , y1) && pd1(x2 , y2) &&
    pd1(x3 , y3) && pd1(x4 , y4) && pd2(x , y) &&
    pd2(x1 , y1) && pd2(x2 , y2) && pd2(x3 , y3) &&
    pd2(x4 , y4);
}
void dfs(int x , int y , int cnt){
	if(x == n && y == m){
        int num = 0;
        bool flag = 0;
		for(re int i = 0; i < 4; i++){
            int nx1 = x + dx[i][0] , ny1 = y + dy[i][0];
            int nx2 = x + dx[i][1] , ny2 = y + dy[i][1];
            int nx3 = x + dx[i][2] , ny3 = y + dy[i][2];
            int nx4 = x + dx[i][3] , ny4 = y + dy[i][3];
            if(PD(x , y , nx1 , ny1 , nx2 , ny2 , nx3 , ny3 , nx4 , ny4)){
                num++ , flag = 1;
                a[x][y] = a[nx1][ny1] = a[nx2][ny2] = a[nx3][ny3] = a[nx4][ny4] = cnt + num;
                break;
            }
        }
        if(ans < cnt + num){
            ans = cnt + num;
            memcpy(anss , a , sizeof(a));
        }
		return;
	}
	int num = 0;
    bool flag = 0;
	for(re int i = 0; i < 4; i++){
		int nx1 = x + dx[i][0] , ny1 = y + dy[i][0];
		int nx2 = x + dx[i][1] , ny2 = y + dy[i][1];
        int nx3 = x + dx[i][2] , ny3 = y + dy[i][2];
        int nx4 = x + dx[i][3] , ny4 = y + dy[i][3];
		if(PD(x , y , nx1 , ny1 , nx2 , ny2 , nx3 , ny3 , nx4 , ny4)){
			num++;
			a[x][y] = a[nx1][ny1] = a[nx2][ny2] = a[nx3][ny3] = a[nx4][ny4] = cnt + num;
			dfs(((y + 1 > m) ? x + 1 : x) , ((y + 1 > m) ? 1 : y + 1) , cnt + 1);
			a[x][y] = a[nx1][ny1] = a[nx2][ny2] = a[nx3][ny3] = a[nx4][ny4] = 0;
            num--;
		}
	}
	dfs(((y + 1 > m) ? x + 1 : x) , ((y + 1 > m) ? 1 : y + 1) , cnt);
}
il void dabiao(){
    if(n == 7 && m == 9){
        printf("10\nAAA.BBB..\n.ACCCBDDD\n.AECFB.D.\nEEECFFFDG\nH.EJFIGGG\nHHHJ.IIIG\nH.JJJI...");
        exit(0);
    }
    if(n == 9 && m == 7){
        printf("10\nAAA.B..\n.ABBBC.\n.AD.BC.\nDDDECCC\nF.DEEEG\nFFFEGGG\nFHIIIJG\n.H.I.J.\nHHHIJJJ");
        exit(0);
    }
    if(n == 8 && m == 8){
        printf("10\nAAA.BCCC\n.ABBBDC.\nEA.FBDC.\nEEEFDDDG\nEHFFFGGG\n.HIII.JG\nHHHIJJJ.\n...I..J.");
        exit(0);
    }
    if(n == 8 && m == 9){
        printf("12\nA.EEE.JJJ\nAAAEHHHJ.\nAB.EFHKJ.\n.BFFFHKKK\nBBBDFIK..\nCDDDGIIIL\nCCCDGILLL\nC..GGG..L");
        exit(0);
    }
    if(n == 9 && m == 8){
        printf("12\nAAA.BCCC\n.ABBBDC.\nEA.FBDC.\nEEEFDDDG\nEHFFFGGG\n.HHHIIIG\nJHKKKIL.\nJJJK.IL.\nJ..K.LLL");
        exit(0);
    }
    if(n == 9 && m == 9){
        printf("13\nAAA.BCCC.\n.ABBB.CD.\n.AE.BFCD.\nEEEFFFDDD\nG.E.HFIII\nGGGJHHHI.\nGK.JHL.IM\n.KJJJLMMM\nKKK.LLL.M");
        exit(0);
    }
    return;
}
int main(){
    scanf("%d%d" , &n , &m);
    dabiao();
    dfs(1 , 1 , 0);
    printf("%d\n" , ans);
    for(re int i = 1; i <= n; i++){
        for(re int j = 1; j <= m; j++){
            if(!anss[i][j]) printf(".");
            else printf("%c" , (char)(anss[i][j] + 'A' - 1));
        }
        printf("\n");
    }
	return 0;
}
```
<https://codeforces.com/problemset/submission/142/197211379>

---

## 作者：yzy4090 (赞：3)

[原题链接](https://www.luogu.com.cn/problem/CF142C) 

**题意**：   
本题要求我们在 $n\times m$ 的方格中放置大小为 $3\times3$ 的 T，可以旋转，但不能重叠。T 形如：  
``` 
### #     #  #
 #  ### ###  #
 #  #     # ###
```  
输出一种可以放置最多 T 的方案，使用不同的大写字母表示不同的 T。  

**思路**：  
我们可以使用搜索的方式枚举所有放置 T 的方案，若当前答案 $nowans$ 大于最终答案 $ans$ 则更新最优解。  
但是一般的搜索会超时，我们需要对搜索进行剪枝。使用 $c_{ij}$ 表示搜索至第 $i$ 行第 $j$ 列个方格时最大放置的 T 数量，可以发现若 $nowans+1<c_{ij}$ 则表明当前方案不会比最后一次更新 $c_{ij}$ 时的方案更好。  
同时我们发现若 $n=m=1$ 则搜索将会越界，所以需要特判。事实上，若 $n<3$ 或 $m<3$ 则均不能放置 T，可以同时特判。  

**代码**：
```cpp
#include<iostream>
#include<cstring>
#define i x
#define j y
#define judge if(cnt+1>=c[x][y])\
{c[x][y]=max(c[x][y],cnt);\
if(y==m-1)dfs(x+1,2,cnt+1);\
else dfs(x,y+1,cnt+1);}
using namespace std;
int n,m,ans,a[15][15],c[15][15];
//a[][] 为01状态数组，其中 a[i][j]=true 当且仅当第 i 行第 j 列的方格被 T 覆盖。
//c[][] 用来剪枝，具体用法见上文。
char b[15][15],d[15][15];
//b[][]，d[][] 用来输出方案。
void dfs(int x,int y,int cnt)
{
	if(x==n)
	{
		if(ans<cnt)
		{
			ans=cnt;
			memcpy(d,b,sizeof(b));
		}
		return;
	}
	//更新方案。
	if(!a[i][j]&&!a[i-1][j]&&!a[i+1][j]&&!a[i-1][j-1]&&!a[i-1][j+1])
	{
		a[i][j]=a[i-1][j]=a[i+1][j]=a[i-1][j-1]=a[i-1][j+1]=1;
		b[i][j]=b[i-1][j]=b[i+1][j]=b[i-1][j-1]=b[i-1][j+1]='A'+cnt;
		judge
		a[i][j]=a[i-1][j]=a[i+1][j]=a[i-1][j-1]=a[i-1][j+1]=0;
		b[i][j]=b[i-1][j]=b[i+1][j]=b[i-1][j-1]=b[i-1][j+1]=0;
		//还原未放置 T 的状态。
	}
	if(!a[i][j]&&!a[i][j-1]&&!a[i][j+1]&&!a[i-1][j+1]&&!a[i+1][j+1])
	{
		a[i][j]=a[i][j-1]=a[i][j+1]=a[i-1][j+1]=a[i+1][j+1]=1;
		b[i][j]=b[i][j-1]=b[i][j+1]=b[i-1][j+1]=b[i+1][j+1]='A'+cnt;
		judge
		a[i][j]=a[i][j-1]=a[i][j+1]=a[i-1][j+1]=a[i+1][j+1]=0;
		b[i][j]=b[i][j-1]=b[i][j+1]=b[i-1][j+1]=b[i+1][j+1]=0;
	}
	if(!a[i][j]&&!a[i-1][j]&&!a[i+1][j]&&!a[i+1][j-1]&&!a[i+1][j+1])
	{
		a[i][j]=a[i-1][j]=a[i+1][j]=a[i+1][j-1]=a[i+1][j+1]=1;
		b[i][j]=b[i-1][j]=b[i+1][j]=b[i+1][j-1]=b[i+1][j+1]='A'+cnt;
		judge
		a[i][j]=a[i-1][j]=a[i+1][j]=a[i+1][j-1]=a[i+1][j+1]=0;
		b[i][j]=b[i-1][j]=b[i+1][j]=b[i+1][j-1]=b[i+1][j+1]=0;
	}
	if(!a[i][j]&&!a[i][j-1]&&!a[i][j+1]&&!a[i-1][j-1]&&!a[i+1][j-1])
	{
		a[i][j]=a[i][j-1]=a[i][j+1]=a[i-1][j-1]=a[i+1][j-1]=1;
		b[i][j]=b[i][j-1]=b[i][j+1]=b[i-1][j-1]=b[i+1][j-1]='A'+cnt;
		judge
		a[i][j]=a[i][j-1]=a[i][j+1]=a[i-1][j-1]=a[i+1][j-1]=0;
		b[i][j]=b[i][j-1]=b[i][j+1]=b[i-1][j-1]=b[i+1][j-1]=0;
	}
	//当可以放置中心点为（x，y）的 T 时，枚举四种情况。
	if(y==m-1)dfs(x+1,2,cnt);
	else dfs(x,y+1,cnt);
	//不放置 T，继续搜索。
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	if(n<3||m<3)
	{
		puts("0");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)putchar('.');
			puts("");
		}
		exit(0);
	}
	//特判不能放置 T 的方格大小。
	dfs(2,2,0);
	//若中心点在边缘则显然不能放置 T，没有枚举的必要，所以可以直接从（2，2）开始，到达第 n 行则结束本次搜索。
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)putchar(d[i][j]==0?'.':d[i][j]);
		puts("");
	}
	return 0;
}
```


---

## 作者：Milthm (赞：2)

## CF142C 题解

~~看到有大佬说爆搜会超时，今天我要为爆搜证明！~~

### 前置知识

- 搜索

- 剪枝

### 题目解法

言归正传，没有任何优化的爆搜肯定会超时。所以我们先写出爆搜代码，然后优化。

首先很容易看出，当 $n$ 和 $m$ 有一个小于等于 $2$ 时，肯定一个形状都放不下，输出 $0$ 然后输出一个空矩阵就可以。

否则我们深搜，因为一个格子只有五种情况（四种形状的方法和什么都不放），所以搜索五种情况就可以了，在每次到最后的时候更新一下答案和要输出的方案矩阵。

然后交上去就可以得到一团黑色。

然后进行优化（剪枝），我们发现，如果你当前放到一个地方，比之前放到这个地方的答案要小很多，那么你就不用接着往下了，因为答案肯定不是最优了。这里我判断的是是否比之前的答案小的值小于等于 $2$ 。

然后就又水了一道紫题。

### AC 代码

```cpp
#include<iostream>
using namespace std;
int n,m,ans;
int v[20][20];
char a[20][20],anss[20][20];
void dfs(int x,int y,int cnt,char now){
	if(x>n){//如果搜索完毕了
		if(cnt>ans){//更新答案和方案矩阵
			ans=cnt;
			for(int i=1;i<=n;++i){
				for(int j=1;j<=m;++j){
					anss[i][j]=a[i][j];
				}
			}
		}
		
		return;
	}
	if(cnt+2<v[x][y])return;//如果比之前小一些，那么就不是最优
	v[x][y]=max(v[x][y],cnt);//更新当前的最大值
   //以下为四种形状的搜索
	if(a[x][y]=='.'&&a[x-1][y]=='.'&&a[x+1][y]=='.'&&a[x-1][y-1]=='.'&&a[x-1][y+1]=='.'){
		a[x][y]=a[x-1][y]=a[x+1][y]=a[x-1][y-1]=a[x-1][y+1]=now;//更新为当前的字母
		if(y+2<=m)dfs(x,y+2,cnt+1,now+1);//往右面递归
		else dfs(x+1,2,cnt+1,now+1);//到头了就往下递归
		a[x][y]=a[x-1][y]=a[x+1][y]=a[x-1][y-1]=a[x-1][y+1]='.';//回溯
	}
    //下面三个同理第一个
	if(a[x][y]=='.'&&a[x][y-1]=='.'&&a[x][y+1]=='.'&&a[x-1][y-1]=='.'&&a[x+1][y-1]=='.'){
		a[x][y]=a[x][y-1]=a[x][y+1]=a[x-1][y-1]=a[x+1][y-1]=now;
		if(y+2<=m)dfs(x,y+2,cnt+1,now+1);
		else dfs(x+1,2,cnt+1,now+1);
		a[x][y]=a[x][y-1]=a[x][y+1]=a[x-1][y-1]=a[x+1][y-1]='.';
	}
	if(a[x][y]=='.'&&a[x][y-1]=='.'&&a[x][y+1]=='.'&&a[x-1][y+1]=='.'&&a[x+1][y+1]=='.'){
		a[x][y]=a[x][y-1]=a[x][y+1]=a[x-1][y+1]=a[x+1][y+1]=now;
		if(y+2<=m)dfs(x,y+2,cnt+1,now+1);
		else dfs(x+1,2,cnt+1,now+1);
		a[x][y]=a[x][y-1]=a[x][y+1]=a[x-1][y+1]=a[x+1][y+1]='.';
	}
	if(a[x][y]=='.'&&a[x-1][y]=='.'&&a[x+1][y]=='.'&&a[x+1][y-1]=='.'&&a[x+1][y+1]=='.'){
		a[x][y]=a[x-1][y]=a[x+1][y]=a[x+1][y-1]=a[x+1][y+1]=now;
		if(y+2<=m)dfs(x,y+2,cnt+1,now+1);
		else dfs(x+1,2,cnt+1,now+1);
		a[x][y]=a[x-1][y]=a[x+1][y]=a[x+1][y-1]=a[x+1][y+1]='.';
	}
   //什么都不选
	if(y==m)dfs(x+1,1,cnt,now);
	else dfs(x,y+1,cnt,now);
}
int main(){
	cin>>n>>m;
	if(n<=2||m<=2){//特判
		cout<<"0\n";
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cout<<'.';
			}
			cout<<endl;
		}
		return 0;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			a[i][j]='.';//记得初始化
		}
	}
	dfs(2,2,0,'A');
	cout<<ans<<endl;//输出答案
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cout<<anss[i][j];
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：COsm0s (赞：2)

DFS。

纯粹的 DFS 肯定过不了。

考虑记忆化。

设 $f_{i,j}$ 为当前搜到的位置 $i, j$ 的 `T` 的个数。

在遍历到 $x, y$ 的点时，如果 `T` 的值已经小于 $f_{x,y}$，则不需要往下搜了。

在搜索的时候，注意以下几个细节：

+ 判定无解。即 $n \leq 2$ 时，大小不足以构成 `T`。

+ 小剪枝：从 $2,2$ 开始搜索，搜索到 $n-1,m-1$ 为止。（至于为什么请读者自行思考）


注意，代码中的 $mp$ 数组代表上文所说 $f$ 数组。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, ma, mp[15][15], f[15][15];
char bj[15][15], sc[15][15];
void dfs(int x, int y, int s) {
	int i, j;
	if (s > ma) {
		ma = s;
		memcpy(sc, bj, sizeof sc);
	}
	if (x == n) {
		return;
	}
	if (!f[x][y] && !f[x - 1][y] && !f[x - 1][y - 1] && !f[x - 1][y + 1] && !f[x + 1][y]) {
		f[x][y] = f[x - 1][y] = f[x - 1][y - 1] = f[x - 1][y + 1] = f[x + 1][y] = 1;
		if (s + 1 >= mp[x][y]) {
			bj[x][y] = bj[x - 1][y] = bj[x - 1][y - 1] = bj[x - 1][y + 1] = bj[x + 1][y] = char(s + 'A');
			mp[x][y] = max(mp[x][y], s);
			if (y == m - 1)dfs(x + 1, 2, s + 1);
			else dfs(x, y + 1, s + 1);
			bj[x][y] = bj[x - 1][y] = bj[x - 1][y - 1] = bj[x - 1][y + 1] = bj[x + 1][y] = '.';
		}
		f[x][y] = f[x - 1][y] = f[x - 1][y - 1] = f[x - 1][y + 1] = f[x + 1][y] = 0;
	}
	if (!f[x][y] && !f[x][y - 1] && !f[x - 1][y + 1] && !f[x][y + 1] && !f[x + 1][y + 1]) {
		f[x][y] = f[x][y - 1] = f[x - 1][y + 1] = f[x][y + 1] = f[x + 1][y + 1] = 1;
		if (s + 1 >= mp[x][y]) {
			bj[x][y] = bj[x][y - 1] = bj[x - 1][y + 1] = bj[x][y + 1] = bj[x + 1][y + 1] = char(s + 'A');
			mp[x][y] = max(mp[x][y], s);
			if (y == m - 1)dfs(x + 1, 2, s + 1);
			else dfs(x, y + 1, s + 1);
			bj[x][y] = bj[x][y - 1] = bj[x - 1][y + 1] = bj[x][y + 1] = bj[x + 1][y + 1] = '.';
		}
		f[x][y] = f[x][y - 1] = f[x - 1][y + 1] = f[x][y + 1] = f[x + 1][y + 1] = 0;
	}
	if (!f[x][y] && !f[x - 1][y] && !f[x + 1][y] && !f[x + 1][y - 1] && !f[x + 1][y + 1]) {
		f[x][y] = f[x - 1][y] = f[x + 1][y] = f[x + 1][y - 1] = f[x + 1][y + 1] = 1;
		if (s + 1 >= mp[x][y]) {
			bj[x][y] = bj[x - 1][y] = bj[x + 1][y] = bj[x + 1][y - 1] = bj[x + 1][y + 1] = char(s + 'A');
			mp[x][y] = max(mp[x][y], s);
			if (y == m - 1)dfs(x + 1, 2, s + 1);
			else dfs(x, y + 1, s + 1);
			bj[x][y] = bj[x - 1][y] = bj[x + 1][y] = bj[x + 1][y - 1] = bj[x + 1][y + 1] = '.';
		}
		f[x][y] = f[x - 1][y] = f[x + 1][y] = f[x + 1][y - 1] = f[x + 1][y + 1] = 0;
	}
	if (!f[x][y] && !f[x - 1][y - 1] && !f[x][y - 1] && !f[x][y + 1] && !f[x + 1][y - 1]) {
		f[x][y] = f[x - 1][y - 1] = f[x][y - 1] = f[x][y + 1] = f[x + 1][y - 1] = 1;
		if (s + 1 >= mp[x][y]) {
			bj[x][y] = bj[x - 1][y - 1] = bj[x][y - 1] = bj[x][y + 1] = bj[x + 1][y - 1] = char(s + 'A');
			mp[x][y] = max(mp[x][y], s);
			if (y == m - 1)dfs(x + 1, 2, s + 1);
			else dfs(x, y + 1, s + 1);
			bj[x][y] = bj[x - 1][y - 1] = bj[x][y - 1] = bj[x][y + 1] = bj[x + 1][y - 1] = '.';
		}
		f[x][y] = f[x - 1][y - 1] = f[x][y - 1] = f[x][y + 1] = f[x + 1][y - 1] = 0;
	}
	if (y == m - 1)dfs(x + 1, 2, s);
	else dfs(x, y + 1, s);
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			sc[i][j] = bj[i][j] = '.';
	}
	if (n < 3 || m < 3) {
		cout << 0 << '\n';
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				cout << sc[i][j];
			puts("");
		}
		exit(0);
	}
	dfs(2, 2, 0);
	cout << ma << '\n';
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			cout << sc[i][j];
		puts("");
	}
	return 0;
}
```

注：代码方面借鉴 @Algae


---

## 作者：___cjy__ (赞：2)

# CF142C Help Caretaker 题解

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf142c)

[题目传送门](https://www.luogu.com.cn/problem/CF142C)

### 题目大意：

有一个大小为 $n \cdot m$ 的平面仓库和一种T形的机器（就像这样）

```
AAA
 A 
 A
```

我们要尽可能多的在这个仓库内放置这种T形的机器，机器可以顺时针或逆时针旋转，但是不可前后翻转，放置时不能重叠。

### 正文:

虽说这是一道~~超水的~~黑题，但是看到 $1 \le n,m \le 9$ 的时候第一反应就是这个题可以用

**暴力打表！**

我们可以定义一个 $3$ 维的字符串数组，前两维分别记录 $n$ 和 $m$,第三维记录当前输出的行下表，每个字符串记录当前输出的这行数据。至于如何打表，这里提供一个简单~~又高效~~的方法：

**人工计算！**

这个题输入数据最多 $81$ 组，在比赛中手写完全来得及，如果说你的 dfs（打表用的）技术不精，写代码和调代码的时间远比你计算答案所耗费的时间与精力多。为了保证稳妥，手算是一个不错的选择。

我们定义一个打表用的字符串数组，将打表的基本框架写好后（[作者用的框架与框架生成代码点这里](https://www.luogu.com.cn/paste/aiir2bje)），直接根据题目要求在框架上展开计算就好了。

比如说在 $n$ 和 $m$ 都等于 $5$ 的情况下，我们要根据框架中这一串代码计算：
```
    f[5][5][1]=".....\n";
    f[5][5][2]=".....\n";
    f[5][5][3]=".....\n";
    f[5][5][4]=".....\n";
    f[5][5][5]=".....\n";
```
这时候，我们就要充分发挥人类智慧了，我们要先确定第一个机器的位置用大写字母```A```表示：
```
    f[5][5][1]="A....\n";
    f[5][5][2]="AAA..\n";
    f[5][5][3]="A....\n";
    f[5][5][4]=".....\n";
    f[5][5][5]=".....\n";
```
接着，我们再确定第二个机器的位置：
```
    f[5][5][1]="A.BBB\n";
    f[5][5][2]="AAAB.\n";
    f[5][5][3]="A..B.\n";
    f[5][5][4]=".....\n";
    f[5][5][5]=".....\n";
```
直到仓库被我们填的足够满，无法继续放置机器，就完成了。（像这样）
```
    f[5][5][1]="A.BBB\n";
    f[5][5][2]="AAAB.\n";
    f[5][5][3]="AD.BC\n";
    f[5][5][4]=".DCCC\n";
    f[5][5][5]="DDD.C\n";
```
注意，在我们计算过程中，如果结果出现空位过多，或者机器之间位置冲突可以酌情考虑推掉重做或者删除一些机器重新计算。

[附上作者打的表](https://www.luogu.com.cn/paste/98b2nt13)

但是，题目还要求统计机器的个数，我们可以用一个字符找到表中 ASCII 值最大的字符（```.```除外），再将该字符的 ASCII 值减```A```的 ASCII 值再加上 $1$，即计算这个字符是第几个大写字母。这样所得的得数就是题目要求统计的机器的个数。

统计机器个数代码：
```cpp
char Max='.';
for(int i=1;i<=n;i++)
	for(int j=0;j<m;j++)
		if(f[n][m][i][j]!='.') 
			Max=max(Max,f[n][m][i][j]);//找ASCII码值最大的字符 
if(Max=='.') cout<<"0\n";//没有更新说明没有机器 
else cout<<int(Max-'A'+1)<<'\n';//计算机器个数 

```
结合打表与统计机器个数的代码，就可以得到 AC 代码。

[AC Code点这里~~](https://www.luogu.com.cn/paste/7o9knyqt)

实测 AC。

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF142C)

## 思路

为什么 dfs 会超时呢？一定是因为你胆子不大，不敢剪枝。

我们可以记录一个时间戳，用于记录搜索的次数。每次搜索时时间戳 $+1$。如果搜索次数太大、快超时了（我这里定的是 $10^8$），那么我们就不搜了，直接输出最后的结果并结束程序。

我们读入数据后，如果 $n<3$ 或者 $m<3$，很显然一个都放不下，输出 $0$ 和一个空表格即可。

能放的话，我们进行搜索。搜索时记录当前位置 $(x,y)$，当前放的个数 $cnt$，和当前要放入的字母。枚举四个方向，如果这个方向没有阻挡物，直接放入并继续搜索。当然，如果放不进去就向下一个格搜索。搜完一行再搜下一行。

每次搜索时判断当前放入个数是否比之前放入的总数多，如果是就记录，并更新答案表格。最后输出最多放入的个数和答案表格。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=20;
int n,m,ans,tim;
char mp[N][N],res[N][N];//mp[][] 是当前的表格，res[][] 是答案表格。
inline void dfs(int x,int y,int cnt,char let){
	if(ans<cnt){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)res[i][j]=mp[i][j];
		}
	}	
	ans=max(ans,cnt);
	++tim;
	if(tim>1e8){//过了 10^8 次就快超时了，所以我们直接输出。
		cout<<ans<<"\n";
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)cout<<res[i][j];
			cout<<"\n";
		}
		exit(0);
	}
	if(x+1==n)return ;
	for(int i=1;i<=4;++i){
		if(i==1){
			if(mp[x][y]=='.'&&mp[x+1][y]=='.'&&mp[x+1][y+1]=='.'&&mp[x+1][y+2]=='.'&&mp[x+2][y]=='.'){
			   	mp[x][y]=mp[x+1][y]=mp[x+1][y+1]=mp[x+1][y+2]=mp[x+2][y]=let;
			   	if(y+2==m)dfs(x+1,1,cnt+1,let+1);
			   	else dfs(x,y+1,cnt+1,let+1);
			   	mp[x][y]=mp[x+1][y]=mp[x+1][y+1]=mp[x+1][y+2]=mp[x+2][y]='.';
			}
		}
		if(i==2){
			if(mp[x][y+1]=='.'&&mp[x+1][y+1]=='.'&&mp[x+2][y]=='.'&&mp[x+2][y+1]=='.'&&mp[x+2][y+2]){
			   	mp[x][y+1]=mp[x+1][y+1]=mp[x+2][y]=mp[x+2][y+1]=mp[x+2][y+2]=let;
			   	if(y+2==m)dfs(x+1,1,cnt+1,let+1);
			   	else dfs(x,y+1,cnt+1,let+1);
			   	mp[x][y+1]=mp[x+1][y+1]=mp[x+2][y]=mp[x+2][y+1]=mp[x+2][y+2]='.';
			}
		}
		if(i==3){
			if(mp[x][y]=='.'&&mp[x][y+1]=='.'&&mp[x][y+2]=='.'&&mp[x+1][y+1]=='.'&&mp[x+2][y+1]){
			   	mp[x][y]=mp[x][y+1]=mp[x][y+2]=mp[x+1][y+1]=mp[x+2][y+1]=let;
			   	if(y+2==m)dfs(x+1,1,cnt+1,let+1);
			   	else dfs(x,y+1,cnt+1,let+1);
			   	mp[x][y]=mp[x][y+1]=mp[x][y+2]=mp[x+1][y+1]=mp[x+2][y+1]='.';
			}
		}
		if(i==4){
			if(mp[x][y+2]=='.'&&mp[x+1][y]=='.'&&mp[x+1][y+1]=='.'&&mp[x+1][y+2]=='.'&&mp[x+2][y+2]){
			   	mp[x][y+2]=mp[x+1][y]=mp[x+1][y+1]=mp[x+1][y+2]=mp[x+2][y+2]=let;
			   	if(y+2==m)dfs(x+1,1,cnt+1,let+1);
			   	else dfs(x,y+1,cnt+1,let+1);
			   	mp[x][y+2]=mp[x+1][y]=mp[x+1][y+1]=mp[x+1][y+2]=mp[x+2][y+2]='.';
			}
		}
	}
	if(y+2==m)dfs(x+1,1,cnt,let);
	else dfs(x,y+1,cnt,let);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)mp[i][j]='.';
	}
	if(n<3||m<3){
		cout<<"0\n";
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)cout<<'.';
			cout<<"\n";
		}
		return 0;
	}
	dfs(1,1,0,'A');//从初始位置开始搜。
	cout<<ans<<"\n";
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)cout<<res[i][j];
		cout<<"\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/126768009)

---

## 作者：qinmingze (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF142C)

### 思路

本题是一道搜索题。

我们只需要用题目给出的 $4$ 种情况进行不断地尝试就可以了。但是在我们写完之后，会发现会有一些测试点是超时的，这时我们只需要进行卡常就行了。

而当 $n<3$ 或 $m<3$ 的时候，肯定是一个都放不下的，因此我们输出 $0$ 就可以结束了。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 15;

int x[N], y[N], ans = 0, n, m;

int c = 0;

int mp[N][N][N] , dis[N][N];

int mp_vis[N][N], ansa[N][N];

void dfs(int x, int y, int cnt){
	c++;
	if(c > 89988500){//卡常。
		cout << ans << endl;//直接输出答案。
		for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(ansa[i][j] == 0)cout << '.';
			else cout << char(ansa[i][j] + 'A' - 1);
		}
		cout << endl;
	}
		exit(0);
	}
	if(x == n){
		if(cnt > ans){//找最优答案。
			ans = cnt;
			for(int i = 1; i <= n; i++){
				for(int j = 1; j <= m; j++){
					ansa[i][j] = mp_vis[i][j];//更新最优答案的状态。
				}
			}
		}
		return ;
	}
	//if(ans == n * m / 5)return ;
	for(int k = 1; k <= 4; k++){//四种情况
		if(k == 1 && !mp_vis[x - 1][y - 1] && !mp_vis[x][y - 1] && !mp_vis[x + 1][y - 1] && !mp_vis[x][y] && !mp_vis[x][y + 1]){
			if(cnt + 2 < dis[x][y])continue;
			dis[x][y] = cnt + 1;
			mp_vis[x - 1][y - 1] = mp_vis[x][y - 1] = mp_vis[x + 1][y - 1] = mp_vis[x][y] = mp_vis[x][y + 1] = cnt + 1;
			//ans = max(ans, cnt + 1);
			if(y == m - 1)dfs(x + 1, 2, cnt + 1);
			else dfs(x, y + 1, cnt + 1);
			mp_vis[x - 1][y - 1] = mp_vis[x][y - 1] = mp_vis[x + 1][y - 1] = mp_vis[x][y] = mp_vis[x][y + 1] = 0;
		}else if(k == 2 && !mp_vis[x - 1][y] && !mp_vis[x][y] && !mp_vis[x + 1][y - 1] && !mp_vis[x + 1][y] && !mp_vis[x + 1][y + 1]){
			if(cnt + 2 < dis[x][y])continue;
			dis[x][y] = cnt + 1;
			mp_vis[x - 1][y] = mp_vis[x][y] = mp_vis[x + 1][y - 1] = mp_vis[x + 1][y] = mp_vis[x + 1][y + 1] = cnt + 1;
			//ans = max(ans, cnt + 1);
			if(y == m - 1)dfs(x + 1, 2, cnt + 1);
			else dfs(x, y + 1, cnt + 1);
			mp_vis[x - 1][y] = mp_vis[x][y] = mp_vis[x + 1][y - 1] = mp_vis[x + 1][y] = mp_vis[x + 1][y + 1] = 0;
		}else if(k == 3 && !mp_vis[x - 1][y + 1] && !mp_vis[x][y - 1] && !mp_vis[x][y] && !mp_vis[x][y + 1] && !mp_vis[x + 1][y + 1]){
			if(cnt + 2 < dis[x][y])continue;
			dis[x][y] = cnt + 1;
			mp_vis[x - 1][y + 1] = mp_vis[x][y - 1] = mp_vis[x][y] = mp_vis[x][y + 1] = mp_vis[x + 1][y + 1] = cnt + 1;
			//ans = max(ans, cnt + 1);
			if(y == m - 1)dfs(x + 1, 2, cnt + 1);
			else dfs(x, y + 1, cnt + 1);
			mp_vis[x - 1][y + 1] = mp_vis[x][y - 1] = mp_vis[x][y] = mp_vis[x][y + 1] = mp_vis[x + 1][y + 1] = 0;
		}else if(k == 4 && !mp_vis[x - 1][y - 1] && !mp_vis[x - 1][y] && !mp_vis[x - 1][y + 1] && !mp_vis[x][y] && !mp_vis[x + 1][y]){
			if(cnt + 2 < dis[x][y])continue;
			dis[x][y] = cnt + 1;
			mp_vis[x - 1][y - 1] = mp_vis[x - 1][y] = mp_vis[x - 1][y + 1] = mp_vis[x][y] = mp_vis[x + 1][y] = cnt + 1;
			//ans = max(ans, cnt + 1);
			if(y == m - 1)dfs(x + 1, 2, cnt + 1);
			else dfs(x, y + 1, cnt + 1);
		    mp_vis[x - 1][y - 1] = mp_vis[x - 1][y] = mp_vis[x - 1][y + 1] = mp_vis[x][y] = mp_vis[x + 1][y] = 0;
		}
	}
   //跳过。
	if(y == m - 1)dfs(x + 1, 2, cnt);
    else dfs(x, y + 1, cnt);
}

int main(){
	scanf("%d%d", &n, &m);
	if(n < 3 || m < 3){//肯定不行。
	    cout << 0 << endl;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				cout << '.';
			}
			cout << endl;
		}
		
		return 0;
	}
	//memset(dis, -0x3f, sizeof dis);
	dfs(2, 2, 0);
  //输出答案。
	cout << ans << endl;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(ansa[i][j] == 0)cout << '.';
			else cout << char(ansa[i][j] + 'A' - 1);
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：littleqwq (赞：1)

这道题其实和 [P1380](https://www.luogu.com.cn/problem/P1380) 特别像，可以说就是它的强化版。这道题呢，因为搜索比较麻烦，我就手打，花了两天打了个表，有错可私信，这道题你可以先在草稿本上列出来，然后找出最优方案，然后填上去，慢慢的就会领悟秘诀了，然后如果你没有 AC 可以对照以下代码！！！你不仅可以把他当做题解，也可以当做找错的样本。

由于码量比较大所以放在剪切板内，[代码链接](https://www.luogu.com.cn/paste/y9mgq6cx)。

注：特判是因为一个T型需要 $3 × 3$ 的格子。

---

## 作者：Code_AC (赞：1)

[博客食用效果更佳](https://www.cnblogs.com/yhx-error/p/16411195.html)

## 题目大意：
就是给你一个 $ n \times m $ 的仓库，起初为空，然后让你往里边放很多类似 $T$ 字形的机器（如样例所示），问你最多能放多少，然后把放法输出来。

## 题目分析：
很明显，这道题应该是给了 spj 的，所以输出不用过多考虑，我们来分析一下数据范围。

这道题虽然 $ n \times m $ 只有 $ 9 \times 9 $ 的数据，但是爆搜明显是过不了的，所以我们考虑一些剪枝的策略，比如可行性剪枝、最优解剪枝和唯一解剪枝。

### 剪枝策略：

**1.首先我们考虑一些有唯一解的答案：**

当 $ n = 7 $ 且 $ m = 8 $ 时，答案应为 $ 9 $，放法为

```
A . D D D . . H

A A A D F H H H

A . B D F F F H

B B B E F I I I

. C B E . G I .

. C E E E G I .

C C C . G G G .
```

当 $ n = 7 $ 且 $ m = 9 $ 时，答案应为 $ 10 $，放法为

```
A A A . B B B . .

. A C C C B D D D

E A . C . B F D .

E E E C F F F D .

E I G G G J F . H

. I . G . J H H H

I I I G J J J . H
```

当 $ n = 8 $ 且 $ m = 9 $ 时，答案应为 $ 12 $，放法为

```
A . E E E . J J J

A A A E H H H J .

A B . E F H K J .

. B F F F H K K K

B B B D F I K . .

C D D D G I I I L

C C C D G I L L L

C . . G G G . . L
```

当 $ n = 9 $ 且 $ m = 8 $ 时，答案应为 $ 12 $，放法为

```
A A A . B C C C

. A B B B D C .

E A . F B D C .

E E E F D D D G

E H F F F G G G

. H H H I I I G

J H K K K I L .

J J J K . I L .

J . . K . L L L
```

当 $ n = 9 $ 且 $ m = 9 $ 时，答案应为 $ 13 $，放法为

```
A A A . B C C C .

. A B B B . C D .

. A E . B F C D .

E E E F F F D D D

G . E . H F I I I

G G G J H H H I .

G K . J H L . I M

. K J J J L M M M

K K K . L L L . M
```

**2.考虑一些范围限制的剪枝：**

这是一个考场上不是特别实用的剪枝，经过本人粗略计算加尝试，在搜索次数达到一定量时，答案就已经求出并且不会改变，不过这个一定量需要自行探索。

所以我们可以记录一下递归次数，然后当次数超过某一个界限时就直接输出结果并结束整个搜索过程，当然，我的代码中用的界限并不是唯一的，目的只是为了让它不超时。


这里将 AC 代码搬上来：

**Code（包含少量注释）**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=20;

inline int read()
{
	register int x=0,f=1;
	register char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}//快读

int n,m,cnt,maxi;
char ma[MAXN][MAXN],ans[MAXN][MAXN];

inline void dfs(int x,int now)//搜索过程
{
	cnt++;//递归的次数
	if(x>maxi)//若目前搜索到的结果已经超过之前的最大值，就更新答案
	{
		maxi=x;
		memcpy(ans,ma,sizeof(ans));
	}
	if(cnt>4500000)//数据范围限制剪枝
	{
		printf("%d\n",maxi);
		for(register int i=1;i<=n;i++)
		{
			for(register int j=1;j<=m;j++)
				printf("%c",ans[i][j]);
			puts("");
		}
		exit(0);
	}
	for(register int i=1;i<=n;i++)//这里的循环用来判上下左右四个方向的机器
		for(register int j=1;j<=m;j++)
			if(ma[i][j]=='.')
			{
				// xxx
				// .x.
				// .x.
				if(ma[i][j+1]=='.'&&ma[i][j+2]=='.'&&ma[i+1][j+1]=='.'&&ma[i+2][j+1]=='.')
				{
					ma[i][j]=ma[i][j+1]=ma[i][j+2]=ma[i+1][j+1]=ma[i+2][j+1]=char(now+'A');
					dfs(x+1,now+1);
					ma[i][j]=ma[i][j+1]=ma[i][j+2]=ma[i+1][j+1]=ma[i+2][j+1]='.';
				}
				// x..
				// xxx
				// x..
				if(ma[i+1][j]=='.'&&ma[i+2][j]=='.'&&ma[i+1][j+1]=='.'&&ma[i+1][j+2]=='.')
				{
					ma[i][j]=ma[i+1][j]=ma[i+2][j]=ma[i+1][j+1]=ma[i+1][j+2]=char(now+'A');
					dfs(x+1,now+1);
					ma[i][j]=ma[i+1][j]=ma[i+2][j]=ma[i+1][j+1]=ma[i+1][j+2]='.';
				}
				// .x.
				// .x.
				// xxx
				if(j>=2)
					if(ma[i+1][j]=='.'&&ma[i+2][j]=='.'&&ma[i+2][j-1]=='.'&&ma[i+2][j+1]=='.')
					{
						ma[i][j]=ma[i+1][j]=ma[i+2][j]=ma[i+2][j-1]=ma[i+2][j+1]=char(now+'A');
						dfs(x+1,now+1);
						ma[i][j]=ma[i+1][j]=ma[i+2][j]=ma[i+2][j-1]=ma[i+2][j+1]='.';
					}
				// ..x
				// xxx
				// ..x
				if(j>=3)
					if(ma[i+1][j-2]=='.'&&ma[i+1][j-1]=='.'&&ma[i+1][j]=='.'&&ma[i+2][j]=='.')
					{
						ma[i][j]=ma[i+1][j-2]=ma[i+1][j-1]=ma[i+1][j]=ma[i+2][j]=char(now+'A');
						dfs(x+1,now+1);
						ma[i][j]=ma[i+1][j-2]=ma[i+1][j-1]=ma[i+1][j]=ma[i+2][j]='.';
					}
			}
}

int main()
{
	n=read(),m=read();
	if(n==7&&m==8)//特殊情况
	{
		printf("9\n");
		printf("A.DDD..H\nAAADFHHH\nA.BDFFFH\nBBBEFIII\n.CBE.GI.\n.CEEEGI.\nCCC.GGG.");
		return 0;
	}
	if(n==7&&m==9)
	{
		printf("10\n");
		printf("AAA.BBB..\n.ACCCBDDD\nEA.C.BFD.\nEEECFFFD.\nEIGGGJF.H\n.I.G.JHHH\nIIIGJJJ.H");
		return 0;
	} 
	if(n==8&&m==9)
	{
		printf("12\n");
		printf("A.EEE.JJJ\nAAAEHHHJ.\nAB.EFHKJ.\n.BFFFHKKK\nBBBDFIK..\nCDDDGIIIL\nCCCDGILLL\nC..GGG..L");
		return 0;
	}	
	if(n==9&&m==8)
	{
		printf("12\n");
		printf("AAA.BCCC\n.ABBBDC.\nEA.FBDC.\nEEEFDDDG\nEHFFFGGG\n.HHHIIIG\nJHKKKIL.\nJJJK.IL.\nJ..K.LLL");
		return 0;
	}
	if(n==9&&m==9)
	{
		printf("13\n");
		printf("AAA.BCCC.\n.ABBB.CD.\n.AE.BFCD.\nEEEFFFDDD\nG.E.HFIII\nGGGJHHHI.\nGK.JHL.IM\n.KJJJLMMM\nKKK.LLL.M");
		return 0;
	}
	memset(ma,'#',sizeof(ma));//将仓库外的位置设为‘#’，以防越界
	for(register int i=1;i<=n;i++)//将仓库清空
		for(register int j=1;j<=m;j++)
			ma[i][j]='.';//
	memcpy(ans,ma,sizeof(ans));//将答案数组进行同样操作
	dfs(0,0);//搜索
	printf("%d\n",maxi);
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=m;j++)
			printf("%c",ans[i][j]);
		puts("");
	}
	return 0;
}
```

[实测AC](https://www.luogu.com.cn/record/77869792)

---

## 作者：long_long (赞：1)

这种题数据好多，容易dfs寻错，所以还是打表大法好。

# 题目大意：

一个n* m的平面仓库里面要放一种T形机器，形状像这样：

```
AAA
 A
 A
```
机器可以顺时针或逆时针旋转，不可前后翻转，放置时不能重叠，问最多能放多少个机器。

(1<=n,m<=9)

其实可以搜，但太麻烦了，所以用打表。

# 思路：

首先一个打表数组（见程序），比较长。

```
string dabiao[]={"0\n.\n","0\n..\n","0\n...\n","0\n....\n","0\n.....\n","0\n......\n","0\n.......\n","0\n........\n","0\n.........\n","0\n.\n.\n","0\n..\n..\n","0\n...\n...\n","0\n....\n....\n","0\n.....\n.....\n","0\n......\n......\n","0\n.......\n.......\n","0\n........\n........\n","0\n.........\n.........\n","0\n.\n.\n.\n","0\n..\n..\n..\n","1\nAAA\n.A.\n.A.\n","1\nAAA.\n.A..\n.A..\n","2\nAAA.B\n.ABBB\n.A..B\n","2\nAAABBB\n.A..B.\n.A..B.\n","3\nAAACBBB\n.A.C.B.\n.ACCCB.\n","3\nAAABBB.C\n.A..BCCC\n.A..B..C\n","4\nAAADBBB.C\n.A.D.BCCC\n.ADDDB..C\n","0\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n","1\nAAA\n.A.\n.A.\n...\n","2\nAAA.\n.AB.\n.AB.\n.BBB\n","2\nAAA..\n.ABBB\n.A.B.\n...B.\n","3\nAAABBB\n.AC.B.\n.AC.B.\n.CCC..\n","4\nAAABBB.\n.AC.BD.\n.AC.BD.\n.CCCDDD\n","4\nAAABBB..\n.AD.BCCC\n.AD.B.C.\n.DDD..C.\n","5\nAAABBBCCC\n.AD.BE.C.\n.AD.BE.C.\n.DDDEEE..\n","0\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n","2\nAAA\n.A.\nBA.\nBBB\nB..\n","2\nAAA.\n.A..\nBA..\nBBB.\nB...\n","4\nAAA.B\n.ABBB\nCA.DB\nCCCD.\nC.DDD\n","4\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC..D..\n","5\nAAABBB.\n.A..BD.\nCA.EBD.\nCCCEDDD\nC.EEE..\n","6\nAAABBB.C\n.A..BCCC\nDA.EB.FC\nDDDEEEF.\nD..E.FFF\n","7\nAAA.BBB.D\n.ACCCBDDD\nEA.CFB.GD\nEEECFFFG.\nE...F.GGG\n","0\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n","2\nAAA\n.A.\nBA.\nBBB\nB..\n...\n","3\nAAA.\n.A..\nBA..\nBBBC\nBCCC\n...C\n","4\nAAA..\n.ABBB\nCA.B.\nCCCBD\nC.DDD\n....D\n","5\nAAABBB\n.A..B.\n.AC.B.\n.ECCCD\n.ECDDD\nEEE..D\n","6\nAAA.BBB\n.AC..B.\n.ACCCB.\nE.CFDDD\nEEEF.D.\nE.FFFD.\n","7\nAAABBB..\n.AD.BCCC\n.AD.B.C.\nEDDDG.CF\nEEE.GFFF\nE..GGG.F\n","8\nAAABBBCCC\n.AD.B..C.\n.AD.BE.C.\nFDDDHEEEG\nFFF.HEGGG\nF..HHH..G\n","0\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n","3\nAAA\n.A.\nBA.\nBBB\nB.C\nCCC\n..C\n","4\nAAA.\n.AB.\n.AB.\nCBBB\nCCCD\nCDDD\n...D\n","5\nAAA..\n.ABBB\nCA.B.\nCCCB.\nCEDDD\n.E.D.\nEEED.\n","6\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nCE.DF.\n.EEEF.\n.E.FFF\n","8\nAAAC..B\n.A.CBBB\nDACCCEB\nDDDEEE.\nDHFFFEG\n.H.FGGG\nHHHF..G\n","9\nAAA.BBB.\n.ACCCBE.\n.ADC.BE.\nDDDCFEEE\nG.DIFFFH\nGGGIFHHH\nG.III..H\n","10\nAAA.BBB..\n.ACCCBDDD\n.AECFB.D.\nEEECFFFDG\nH.EJFIGGG\nHHHJ.IIIG\nH.JJJI...\n","0\n.\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n..\n","3\nAAA\n.A.\nBA.\nBBB\nB..\nCCC\n.C.\n.C.\n","4\nAAA.\n.A..\nBA..\nBBB.\nBCCC\n.DC.\n.DC.\nDDD.\n","6\nAAA..\n.ABBB\nCA.B.\nCCCBD\nC.DDD\nEEEFD\n.E.F.\n.EFFF\n","7\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC.ED..\n.GEEEF\n.GEFFF\nGGG..F\n","9\nAAA.BBB\n.ACCCB.\nDA.CEB.\nDDDCEEE\nDFFFE.G\n.IFHGGG\n.IFHHHG\nIIIH...\n","10\nAAABBB.C\n.A..BCCC\nDA.EB.FC\nDDDEEEF.\nD..EHFFF\nGGGJHHHI\n.G.JHIII\n.GJJJ..I\n","12\nAAA.BBB.D\n.ACCCBDDD\nEA.CFB.GD\nEEECFFFG.\nE..HFIGGG\nJHHHLIIIK\nJJJHLIKKK\nJ..LLL..K\n","0\n.\n.\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n..\n..\n","4\nAAA\n.A.\nBA.\nBBB\nB.C\nCCC\nD.C\nDDD\nD..\n","5\nAAA.\n.A..\nBA..\nBBBC\nBCCC\nD..C\nDDDE\nDEEE\n...E\n","7\nAAA..\n.ABBB\nCA.B.\nCCCBD\nCEDDD\n.EEED\nGEFFF\nGGGF.\nG..F.\n","8\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC.ED..\nEEEFFF\nG.EHF.\nGGGHF.\nG.HHH.\n","10\nAAABBB.\n.A..BD.\nCA.EBD.\nCCCEDDD\nCFEEE.G\n.FFFGGG\nIFHHHJG\nIIIH.J.\nI..HJJJ\n","12\nAAAC.BBB\n.ADCCCB.\n.ADCE.B.\nFDDDEEEG\nFFFHEGGG\nFHHHIIIG\nJJJHKIL.\n.JKKKIL.\n.J..KLLL\n","13\nAAABBB..C\n.A..BDCCC\nEA.GBDDDC\nEEEG.DFFF\nEHGGG.IF.\n.HHHIIIF.\nKHJJJMI.L\nKKKJ.MLLL\nK..JMMM.L\n"};

```

然后照常输入n,m。

之后直接输出 dabiao[(n-1)*9+(m-1)]。

```
int main(){
	int n,m;
    cin>>n>>m;
    cout<<dabiao[(n-1)*9+(m-1)];
    return 0;
}
```

# 程序：

```
#include<string>
#include<iostream>
using namespace std; 
string dabiao[]={"0\n.\n","0\n..\n","0\n...\n","0\n....\n","0\n.....\n","0\n......\n","0\n.......\n","0\n........\n","0\n.........\n","0\n.\n.\n","0\n..\n..\n","0\n...\n...\n","0\n....\n....\n","0\n.....\n.....\n","0\n......\n......\n","0\n.......\n.......\n","0\n........\n........\n","0\n.........\n.........\n","0\n.\n.\n.\n","0\n..\n..\n..\n","1\nAAA\n.A.\n.A.\n","1\nAAA.\n.A..\n.A..\n","2\nAAA.B\n.ABBB\n.A..B\n","2\nAAABBB\n.A..B.\n.A..B.\n","3\nAAACBBB\n.A.C.B.\n.ACCCB.\n","3\nAAABBB.C\n.A..BCCC\n.A..B..C\n","4\nAAADBBB.C\n.A.D.BCCC\n.ADDDB..C\n","0\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n","1\nAAA\n.A.\n.A.\n...\n","2\nAAA.\n.AB.\n.AB.\n.BBB\n","2\nAAA..\n.ABBB\n.A.B.\n...B.\n","3\nAAABBB\n.AC.B.\n.AC.B.\n.CCC..\n","4\nAAABBB.\n.AC.BD.\n.AC.BD.\n.CCCDDD\n","4\nAAABBB..\n.AD.BCCC\n.AD.B.C.\n.DDD..C.\n","5\nAAABBBCCC\n.AD.BE.C.\n.AD.BE.C.\n.DDDEEE..\n","0\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n","2\nAAA\n.A.\nBA.\nBBB\nB..\n","2\nAAA.\n.A..\nBA..\nBBB.\nB...\n","4\nAAA.B\n.ABBB\nCA.DB\nCCCD.\nC.DDD\n","4\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC..D..\n","5\nAAABBB.\n.A..BD.\nCA.EBD.\nCCCEDDD\nC.EEE..\n","6\nAAABBB.C\n.A..BCCC\nDA.EB.FC\nDDDEEEF.\nD..E.FFF\n","7\nAAA.BBB.D\n.ACCCBDDD\nEA.CFB.GD\nEEECFFFG.\nE...F.GGG\n","0\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n","2\nAAA\n.A.\nBA.\nBBB\nB..\n...\n","3\nAAA.\n.A..\nBA..\nBBBC\nBCCC\n...C\n","4\nAAA..\n.ABBB\nCA.B.\nCCCBD\nC.DDD\n....D\n","5\nAAABBB\n.A..B.\n.AC.B.\n.ECCCD\n.ECDDD\nEEE..D\n","6\nAAA.BBB\n.AC..B.\n.ACCCB.\nE.CFDDD\nEEEF.D.\nE.FFFD.\n","7\nAAABBB..\n.AD.BCCC\n.AD.B.C.\nEDDDG.CF\nEEE.GFFF\nE..GGG.F\n","8\nAAABBBCCC\n.AD.B..C.\n.AD.BE.C.\nFDDDHEEEG\nFFF.HEGGG\nF..HHH..G\n","0\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n","3\nAAA\n.A.\nBA.\nBBB\nB.C\nCCC\n..C\n","4\nAAA.\n.AB.\n.AB.\nCBBB\nCCCD\nCDDD\n...D\n","5\nAAA..\n.ABBB\nCA.B.\nCCCB.\nCEDDD\n.E.D.\nEEED.\n","6\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nCE.DF.\n.EEEF.\n.E.FFF\n","8\nAAAC..B\n.A.CBBB\nDACCCEB\nDDDEEE.\nDHFFFEG\n.H.FGGG\nHHHF..G\n","9\nAAA.BBB.\n.ACCCBE.\n.ADC.BE.\nDDDCFEEE\nG.DIFFFH\nGGGIFHHH\nG.III..H\n","10\nAAA.BBB..\n.ACCCBDDD\n.AECFB.D.\nEEECFFFDG\nH.EJFIGGG\nHHHJ.IIIG\nH.JJJI...\n","0\n.\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n..\n","3\nAAA\n.A.\nBA.\nBBB\nB..\nCCC\n.C.\n.C.\n","4\nAAA.\n.A..\nBA..\nBBB.\nBCCC\n.DC.\n.DC.\nDDD.\n","6\nAAA..\n.ABBB\nCA.B.\nCCCBD\nC.DDD\nEEEFD\n.E.F.\n.EFFF\n","7\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC.ED..\n.GEEEF\n.GEFFF\nGGG..F\n","9\nAAA.BBB\n.ACCCB.\nDA.CEB.\nDDDCEEE\nDFFFE.G\n.IFHGGG\n.IFHHHG\nIIIH...\n","10\nAAABBB.C\n.A..BCCC\nDA.EB.FC\nDDDEEEF.\nD..EHFFF\nGGGJHHHI\n.G.JHIII\n.GJJJ..I\n","12\nAAA.BBB.D\n.ACCCBDDD\nEA.CFB.GD\nEEECFFFG.\nE..HFIGGG\nJHHHLIIIK\nJJJHLIKKK\nJ..LLL..K\n","0\n.\n.\n.\n.\n.\n.\n.\n.\n.\n","0\n..\n..\n..\n..\n..\n..\n..\n..\n..\n","4\nAAA\n.A.\nBA.\nBBB\nB.C\nCCC\nD.C\nDDD\nD..\n","5\nAAA.\n.A..\nBA..\nBBBC\nBCCC\nD..C\nDDDE\nDEEE\n...E\n","7\nAAA..\n.ABBB\nCA.B.\nCCCBD\nCEDDD\n.EEED\nGEFFF\nGGGF.\nG..F.\n","8\nAAABBB\n.A..B.\nCA.DB.\nCCCDDD\nC.ED..\nEEEFFF\nG.EHF.\nGGGHF.\nG.HHH.\n","10\nAAABBB.\n.A..BD.\nCA.EBD.\nCCCEDDD\nCFEEE.G\n.FFFGGG\nIFHHHJG\nIIIH.J.\nI..HJJJ\n","12\nAAAC.BBB\n.ADCCCB.\n.ADCE.B.\nFDDDEEEG\nFFFHEGGG\nFHHHIIIG\nJJJHKIL.\n.JKKKIL.\n.J..KLLL\n","13\nAAABBB..C\n.A..BDCCC\nEA.GBDDDC\nEEEG.DFFF\nEHGGG.IF.\n.HHHIIIF.\nKHJJJMI.L\nKKKJ.MLLL\nK..JMMM.L\n"};//打表数组
int main(){
	int n,m;
	cin>>n>>m;//输入
	cout<<dabiao[9*n+m-10];//输出
	return 0;
}
```



---

