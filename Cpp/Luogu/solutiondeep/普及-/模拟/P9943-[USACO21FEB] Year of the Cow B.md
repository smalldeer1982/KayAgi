# 题目信息

# [USACO21FEB] Year of the Cow B

## 题目描述

Farmer John 的奶牛们得知最近正在庆祝牛年的到来时十分兴奋。牛年总是奶牛们的最爱。

我们知道，中国历法中每一年所对应的生肖遵循 $12$ 年的周期：Ox, Tiger, Rabbit, Dragon, Snake, Horse, Goat, Monkey, Rooster, Dog, Pig, Rat（牛、虎、兔、龙、蛇、马、羊、猴、鸡、狗、猪、鼠），然后回到牛。

奶牛 Bessie 自豪地说她是在许多年前的一个牛年出生的。她的朋友 Elsie 想要知道她与 Bessie 出生相差多少年，并且希望你能够通过查看农场上若干奶牛出生年份之间的关系来帮助她推算。 

## 说明/提示

### 样例解释 1

在以上的输入中，

- Elsie 在 Bessie 之前 $12$ 年出生。
- Mildred 在 Bessie 之前 $9$ 年出生。
- Gretta 在 Bessie 之前 $17$ 年出生。
- Paulina 在 Bessie 之后 $9$ 年出生。

## 样例 #1

### 输入

```
4
Mildred born in previous Dragon year from Bessie
Gretta born in previous Monkey year from Mildred
Elsie born in next Ox year from Gretta
Paulina born in next Dog year from Bessie```

### 输出

```
12```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何根据奶牛出生年份关系计算Bessie与Elsie出生年份差值展开。思路上，多数题解利用生肖12年循环规律，通过设定Bessie出生年份为基准（如0或2021年），根据输入的“previous”或“next”关系及对应生肖，逐年推算或利用公式计算其他奶牛出生年份，进而得出Bessie与Elsie的年份差。算法要点包括用map、数组或字典树等方式存储奶牛信息及生肖对应关系。解决难点在于准确处理不同生肖间年份差计算，以及确保在12年循环内正确推算。

从质量上看，多数题解思路较清晰，但部分代码可读性欠佳，优化程度也有限。综合考虑思路清晰度、代码可读性和优化程度，以下是各题解评分：
1. **作者Harlem**：思路清晰，公式推导明确，代码实现简洁，利用map映射清晰，得4星。
2. **作者OIerWu_829**：思路易懂，通过逐年改变年份模拟，但代码实现稍显繁琐，得3星。
3. **作者TipherethB**：思路较清晰，公式推导详细，但代码中符号定义较多，影响可读性，得3星。
4. **作者HMSVanguard**：提供字典树新思路，但代码长且复杂，对字典树讲解过多，得3星。
5. **作者LHW_Cosset_Idiot**：先给出错误代码分析，再提供正解，思路可借鉴，但代码风格欠佳，得3星。
6. **作者2027zengrihui**：将问题看作最短路问题，但代码实现未充分体现最短路算法优势，得3星。
7. **作者卷王**：思路独特，通过假设Bessie年龄为0遍历计算，代码注释详细，得4星。
8. **作者Vct14**：模拟思路清晰，利用map存储信息，代码简洁明了，得4星。
9. **作者XiaoWhy**：思路清晰，利用假设Bessie年份为0确定其他奶牛年份，代码简洁，得4星。
10. **作者Manki23333333**：采用图论建模搜索，但代码复杂，可读性差，得3星。

### 所选4星题解
1. **作者Harlem**
    - **星级**：4星
    - **关键亮点**：通过推导公式计算奶牛出生年份差值，思路清晰，利用map映射奶牛名称与编号及生肖与编号，代码简洁明了。
    - **核心代码实现思想**：定义两个map分别存储奶牛名称与编号、生肖与编号。通过输入关系，依据推导公式计算每头奶牛与Bessie出生年份差值，最终输出Bessie与Elsie出生年份差值的绝对值。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int c[105],y[205];
string a,b,pd,t,year;
map<string,int> sx={{"Ox",0},{"Tiger",1},{"Rabbit",2},{"Dragon",3},{"Snake",4},{"Horse",5},{"Goat",6},{"Monkey",7},{"Rooster",8},{"Dog",9},{"Pig",10},{"Rat",11}};
map<string,int> id;

int main(){
    cin>>n;
    c[0]=y[0]=0;
    id["Bessie"]=0;
    for(int i=1;i<=n;i++){
        cin>>a>>t>>t>>pd>>year>>t>>t>>b;
        id[a]=i;y[i]=sx[year];
        if(pd=="previous"){
            if(y[i]<y[id[b]]){
                c[i]=c[id[b]]+(y[i]-y[id[b]]);
            }
            else{
                c[i]=c[id[b]]+(y[i]-12-y[id[b]]);
            }
        }
        if(pd=="next"){
            if(y[i]>y[id[b]]){
                c[i]=c[id[b]]+(y[i]-y[id[b]]);
            }
            else{
                c[i]=c[id[b]]+(y[i]+12-y[id[b]]);
            }
        }
    }
    cout<<abs(c[id["Elsie"]]);
    return 0;
}
```
2. **作者卷王**
    - **星级**：4星
    - **关键亮点**：假设Bessie年龄为0，通过遍历输入关系，从已知年龄奶牛推向未知年龄奶牛，保证所有奶牛年龄都能被计算，代码注释详细。
    - **核心代码实现思想**：使用多个map分别存储生肖与编号、奶牛名称与生肖、奶牛名称与年龄关系。通过遍历输入关系，根据“next”或“previous”分情况计算未知奶牛年龄，最终输出Bessie与Elsie年龄差值的绝对值。
    - **核心代码**：
```cpp
signed main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    mp["Ox"] = 0, mp["Tiger"] = 1, mp["Rabbit"] = 2, mp["Dragon"] = 3, mp["Snake"] = 4;
    mp["Horse"] = 5, mp["Goat"] = 6, mp["Monkey"] = 7, mp["Rooster"] = 8;
    mp["Dog"] = 9, mp["Pig"] = 10, mp["Rat"] = 11; 
    year["Bessie"] = "Ox";
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> a[i] >> s >> s >> b[i] >> c[i] >> s >> s >> d[i];
        year[a[i]] = c[i];
    }
    for (int l = 1; l <= n; l++) { 
        for (int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            if((know[d[i]]!= 0 || d[i] == "Bessie") &&!know[a[i]]) {
                vis[i] = 1;
                if(b[i] == "next") { 
                    if(mp[year[d[i]]] < mp[year[a[i]]]) know[a[i]] = know[d[i]] + (mp[year[a[i]]] - mp[year[d[i]]]);
                    else know[a[i]] = know[d[i]] + (12 - mp[year[d[i]]] + mp[year[a[i]]]);
                }
                else {
                    if(mp[year[a[i]]] < mp[year[d[i]]]) know[a[i]] = know[d[i]] - (mp[year[d[i]]] - mp[year[a[i]]]);
                    else know[a[i]] = know[d[i]] - (12 - mp[year[a[i]]] + mp[year[d[i]]]);
                }
            }
        }
    }
    cout << abs(know["Bessie"] - know["Elsie"]);
    return 0;
}
```
3. **作者Vct14**
    - **星级**：4星
    - **关键亮点**：假设Bessie出生于2021年，利用两个map分别记录奶牛生肖和出生年份，通过计算生肖年份差及年龄大小关系确定其他奶牛出生年份，代码简洁高效。
    - **核心代码实现思想**：定义两个map分别存储奶牛名称与生肖、奶牛名称与出生年份。通过输入关系，利用函数计算生肖年份差，根据“previous”或“next”调整差值并计算奶牛出生年份，最后输出Bessie与Elsie出生年份差值的绝对值。
    - **核心代码**：
```cpp
int getc(string D1,string D2,int g){ 
    int d1=getn(D1),d2=getn(D2);
    if(d1==d2) return 12;
    return ((d2-d1)*g+12)%12;
}

int main(){
    int n;cin>>n;
    m1["Bessie"]="Ox";m2["Bessie"]=2021; 
    while(n--){
        string ca,cb,gx,dw,in;
        cin>>ca>>in>>in>>gx>>dw>>in>>in>>cb; 
        int f=1;if(gx=="previous") f=-1; 
        m1[ca]=dw;m2[ca]=m2[cb]+getc(m1[cb],dw,f)*f; 
    } 
    cout<<abs(m2["Elsie"]-m2["Bessie"]);
    return 0;
}
```

### 最优关键思路或技巧
1. **设定基准值**：假设Bessie出生年份为0或2021年，以此为基准推算其他奶牛出生年份，简化问题。
2. **利用map存储关系**：使用map容器建立奶牛名称与编号、生肖与编号或奶牛名称与出生年份等关系，方便快速查找和计算。
3. **分情况推导公式**：根据“previous”和“next”关系，结合生肖顺序，分情况推导出计算奶牛出生年份差值的公式，准确求解。

### 可拓展思路
此类题目属于模拟与逻辑推导结合类型，可拓展到其他具有周期性规律的关系推导问题，如日期推算、周期性任务安排等。类似算法套路是先确定基准值，再根据给定关系和周期规律建立数学模型或逻辑流程进行推导计算。

### 相似知识点洛谷题目推荐
1. **P1035 [NOIP2002 普及组] 级数求和**：涉及简单数学规律模拟与计算，与本题根据规律计算年份差类似。
2. **P1909 [NOIP2016 普及组] 买铅笔**：通过分析不同购买方案进行模拟选择，和本题根据不同条件计算结果思路相似。
3. **P5734 [深基7.例7] 计算阶乘**：围绕阶乘计算规律进行编程实现，锻炼对数学规律的代码实现能力，与本题根据生肖规律计算有相似之处。 

---
处理用时：110.86秒