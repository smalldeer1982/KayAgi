# 题目信息

# [USACO1.2] 命名那个数字 Name That Number

## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。


## 样例 #1

### 输入

```
4734
NMSL
GREG
LSDC
....(太多了不写了)```

### 输出

```
GREG
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕将数字编号转化为字母名字，并在字典中查找匹配名字的问题展开。思路大致可分为两类：一是将字典中的名字转化为数字串，与输入数字串比对；二是根据输入数字生成所有可能字母组合，再在字典中查找。

### 所选题解
- **作者：bjrjk（5星）**
    - **关键亮点**：思路清晰，使用 `vector` 存储字典，通过 `str_trans` 数组快速将字母映射为数字，代码简洁高效，且有剪枝优化。
    - **核心代码**：
```cpp
const char * str_trans = "2223334445556667 77888999";
vector<string> Dict;
string str;
int main(){
    cin >> str;
    string tmp;
    while (cin >> tmp) Dict.push_back(tmp);
    int len = str.length();
    bool global_flag = false;
    for (int i = 0; i < Dict.size(); i++){
        if (len!= Dict[i].length()) continue;
        bool flag = true;
        for (int j = 0; j < len; j++){
            if (str_trans[Dict[i][j] - 'A']!= str[j]){
                flag = false;
                break;
            }
        }
        if (flag){
            cout << Dict[i] << endl;
            global_flag = true;
        }
    }
    if (!global_flag) cout << "NONE" << endl;
}
```
- **作者：cellur925（4星）**
    - **关键亮点**：使用 `map` 建立字母到数字的映射，方便进行字母与数字的转换，代码逻辑清晰。
    - **核心代码**：
```cpp
map<char,int>m;
void init(){
    m['A']=2;m['B']=2;m['C']=2;
    // 其他字母映射...
}
bool check(){
    int lenw=strlen(word);
    if(lenw!=len) return 0;
    for(int i=0;i<len;i++)
        if(m[word[i]]!=(int)(num[i]-'0')) return 0;
    return 1;
}
int main(){
    scanf("%s",num);
    len=strlen(num);
    init();
    while(scanf("%s",word)!=EOF){
        if(check())
            printf("%s\n",word),cnt++;
    }
    if(!cnt) printf("NONE");
    return 0;
}
```
- **作者：Skyjoy（4星）**
    - **关键亮点**：借鉴了 `bjrjk` 的思路，使用 `vector` 存储字典，有剪枝优化，代码注释详细，适合新手学习。
    - **核心代码**：
```cpp
vector<string>dict;
string s,pre="2223334445556667 77888999",t;
int maxn=4617;
bool flag,flagplus;
int main(){
    cin>>s;
    int len=s.size();
    while(maxn--){
        cin>>t;
        dict.push_back(t);
    }
    for(int i=0;i<4617;i++){
        if(len!=dict[i].size()) continue;
        flag=1;
        for(int j=0;j<len;j++){
            if(pre[dict[i][j]-'A']!=s[j]){
                flag=0;
            }
        }
        if(flag){
            cout<<dict[i]<<endl;
            flagplus=1;
        }
    }
    if(!flagplus) cout<<"NONE";
    return 0;
}
```

### 最优关键思路或技巧
- 使用 `vector` 存储字典，方便遍历和管理。
- 利用数组或 `map` 建立字母到数字的映射，快速进行字母与数字的转换。
- 在比较时进行长度剪枝，减少不必要的比较。

### 可拓展之处
同类型题如电话号码组合问题，可根据数字按键生成所有可能字母组合。类似算法套路为枚举所有可能组合，再进行筛选匹配。

### 推荐题目
- P1605 迷宫
- P1036 选数
- P1162 填涂颜色

### 个人心得摘录与总结
- **Kewth**：输入贼坑，洛谷只能用标准输入输出，要注意 `namenum.in` 和 `dict.txt` 的输入顺序，搞反会扣分。
- **Jjxxz233**：在把字母转成键盘数字时采用 `chr2int` 函数，避免打表，同时要注意编号有12位，使用 `int` 会爆掉，可用 `long long` 或 `string` 存储。 

---
处理用时：28.88秒