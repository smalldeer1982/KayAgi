# [HUSTFC 2023] A+B problem

## 题目描述

Walk Alone 是一个字符串大师，在他的眼中每个字符串都表示一个 $26$ 进制的数，具体地说，按照字母表顺序从 $A$ 到 $Z$ 分别对应着十进制下 $0$ 到 $25$，那么 $BA$ 对应十进制下 $26\ (1\times 26+0)$，$BB$ 对应十进制下 $27\ (1\times 26+1)$，以此类推。

Walk Alone 想考考已经习惯了十进制加法的你，给你两个字符串 $s$ 和 $t$，请你计算出他们所表示的 $26$ 进制数的和，即 $s+t$，并同样以字符串形式告诉他，例如 $A+A=A$，$B+C=D$。为了简化问题，$s$ 和 $t$ 分别只包含一个大写字母，但请注意，答案不一定只包含一个大写字母。

## 样例 #1

### 输入

```
A A
```

### 输出

```
A
```

## 样例 #2

### 输入

```
B C
```

### 输出

```
D
```

## 样例 #3

### 输入

```
Z B
```

### 输出

```
BA
```

# 题解

## 作者：Clarinet (赞：11)

[博客食用观感更佳](https://www.luogu.com.cn/blog/Czel-X/ti-xie-7-post)
# 简要题意
有两个字符串 $s$ 和 $t$，代表 26 进制下的数字，求同样用字符串表示的他们的和。
# 分析
我的思路是先将输入的字符串转化为数字相加，再转化为输出结果。

由于输入的只能是两个一位数，所以只有两种情况：结果为一位数或以 $B$ 开头的两位数，分别判断就好。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
int x,y;
int main(){
	cin>>a>>b;
	x=a[0]-'A';
	y=b[0]-'A';
	x+=y;
	if(x<=25){
		char ans='A'+x;
		cout<<ans;
	}
	else{
		cout<<'B';
		char ans='A'+x-26;
		cout<<ans;
	}
}
```
感谢阅读！

---

## 作者：linyukun (赞：5)

## 1. 前言
本文的分析会比较通俗，自己要多去思考，麻烦一定 _仔细全部看完_，有异议、不懂或认为可以优化请私信反馈呢。  

## 2. 题目解析：
输入两个字母，然后计算其相加的值。  
难点在于不是标准的 $26$ 进制，处理困难。  
我们还注意到，数字从 $0$ 开始，于是，可以想到如下思路：  
* 将字母对应的数字抽象为序数，如 $A$ 是数字 $0$，就是第 $0$ 个字母。
* 两个字母的和就是二者序数和所对应的字母组合。如第 $25$ 个和第 $1$ 个相加就是第 $26$ 个组合（样例三）。
## 3. 提示要点：
* **序数从零开始**，也就是说第一个字母是 $B$，第零个才是 $A$。
## 4. 代码写作：
理论存在，实践开始。  
```cpp
#include<bits/stdc++.h>
using namespace std;
char a,b;
int A,B;
string s[1500]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","BA","BB","BC","BD","BE","BF","BG","BH","BI","BJ","BK","BL","BM","BN","BO","BP","BQ","BR","BS","BT","BU","BV","BW","BX","BY","BZ","CA","CB","CC","CD","CE","CF","CG","CH","CI","CJ","CK","CL","CM","CN","CO","CP","CQ","CR","CS","CT","CU","CV","CW","CX","CY","CZ","DA","DB","DC","DD","DE","DF","DG","DH","DI","DJ","DK","DL","DM","DN","DO","DP","DQ","DR","DS","DT","DU","DV","DW","DX","DY","DZ","EA","EB","EC","ED","EE","EF","EG","EH","EI","EJ","EK","EL","EM","EN","EO","EP","EQ","ER","ES","ET","EU","EV","EW","EX","EY","EZ","FA","FB","FC","FD","FE","FF","FG","FH","FI","FJ","FK","FL","FM","FN","FO","FP","FQ","FR","FS","FT","FU","FV","FW","FX","FY","FZ","GA","GB","GC","GD","GE","GF","GG","GH","GI","GJ","GK","GL","GM","GN","GO","GP","GQ","GR","GS","GT","GU","GV","GW","GX","GY","GZ","HA","HB","HC","HD","HE","HF","HG","HH","HI","HJ","HK","HL","HM","HN","HO","HP","HQ","HR","HS","HT","HU","HV","HW","HX","HY","HZ","IA","IB","IC","ID","IE","IF","IG","IH","II","IJ","IK","IL","IM","IN","IO","IP","IQ","IR","IS","IT","IU","IV","IW","IX","IY","IZ","JA","JB","JC","JD","JE","JF","JG","JH","JI","JJ","JK","JL","JM","JN","JO","JP","JQ","JR","JS","JT","JU","JV","JW","JX","JY","JZ","KA","KB","KC","KD","KE","KF","KG","KH","KI","KJ","KK","KL","KM","KN","KO","KP","KQ","KR","KS","KT","KU","KV","KW","KX","KY","KZ","LA","LB","LC","LD","LE","LF","LG","LH","LI","LJ","LK","LL","LM","LN","LO","LP","LQ","LR","LS","LT","LU","LV","LW","LX","LY","LZ","MA","MB","MC","MD","ME","MF","MG","MH","MI","MJ","MK","ML","MM","MN","MO","MP","MQ","MR","MS","MT","MU","MV","MW","MX","MY","MZ","NA","NB","NC","ND","NE","NF","NG","NH","NI","NJ","NK","NL","NM","NN","NO","NP","NQ","NR","NS","NT","NU","NV","NW","NX","NY","NZ","OA","OB","OC","OD","OE","OF","OG","OH","OI","OJ","OK","OL","OM","ON","OO","OP","OQ","OR","OS","OT","OU","OV","OW","OX","OY","OZ","PA","PB","PC","PD","PE","PF","PG","PH","PI","PJ","PK","PL","PM","PN","PO","PP","PQ","PR","PS","PT","PU","PV","PW","PX","PY","PZ","QA","QB","QC","QD","QE","QF","QG","QH","QI","QJ","QK","QL","QM","QN","QO","QP","QQ","QR","QS","QT","QU","QV","QW","QX","QY","QZ","RA","RB","RC","RD","RE","RF","RG","RH","RI","RJ","RK","RL","RM","RN","RO","RP","RQ","RR","RS","RT","RU","RV","RW","RX","RY","RZ","SA","SB","SC","SD","SE","SF","SG","SH","SI","SJ","SK","SL","SM","SN","SO","SP","SQ","SR","SS","ST","SU","SV","SW","SX","SY","SZ","TA","TB","TC","TD","TE","TF","TG","TH","TI","TJ","TK","TL","TM","TN","TO","TP","TQ","TR","TS","TT","TU","TV","TW","TX","TY","TZ","UA","UB","UC","UD","UE","UF","UG","UH","UI","UJ","UK","UL","UM","UN","UO","UP","UQ","UR","US","UT","UU","UV","UW","UX","UY","UZ","VA","VB","VC","VD","VE","VF","VG","VH","VI","VJ","VK","VL","VM","VN","VO","VP","VQ","VR","VS","VT","VU","VV","VW","VX","VY","VZ","WA","WB","WC","WD","WE","WF","WG","WH","WI","WJ","WK","WL","WM","WN","WO","WP","WQ","WR","WS","WT","WU","WV","WW","WX","WY","WZ","XA","XB","XC","XD","XE","XF","XG","XH","XI","XJ","XK","XL","XM","XN","XO","XP","XQ","XR","XS","XT","XU","XV","XW","XX","XY","XZ","YA","YB","YC","YD","YE","YF","YG","YH","YI","YJ","YK","YL","YM","YN","YO","YP","YQ","YR","YS","YT","YU","YV","YW","YX","YY","YZ","ZA","ZB","ZC","ZD","ZE","ZF","ZG","ZH","ZI","ZJ","ZK","ZL","ZM","ZN","ZO","ZP","ZQ","ZR","ZS","ZT","ZU","ZV","ZW","ZX","ZY","ZZ"};
int main(){
	cin>>a>>b;
	A=a-'A';
	B=b-'A';
	cout<<s[A+B];
	return 0;
}
```

当然，这个组合表也可以用程序来生成：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    for(int i=0;i<=25;i++){
    	for(int j=0;j<=25;j++){
    		cout<<"\"";
    		if(i!=0)cout<<char('A'+i);
    		cout<<char('A'+j)<<"\",";
		}
	}
}
```

## 5. 总结鸣谢：
**感谢管理大大的的审核。**

---

