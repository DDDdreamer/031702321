#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <regex>
using namespace std;

string addr;	//地址变量
string direct_city[4] = { "北京市","上海市","天津市","重庆市" };//直辖市
string direct_cities[4][40] = {
	"朝阳区","海淀区","通州区","房山区","丰台区","昌平区","大兴区","顺义区","西城区","延庆县","石景山区","宣武区","怀柔区","崇文区","密云县","东城区","门头沟区","平谷区","","","","","","","",  "","","","","","","","","","","","","","","",\
	"松江区","宝山区","金山区","嘉定区","南汇区","青浦区","浦东新区","奉贤区","闵行区","徐汇区","静安区","黄浦区","普陀区","杨浦区","虹口区","闸北区","长宁区","崇明县","卢湾区","","","","","","",  "","","","","","","","","","","","","","","",\
	"和平区","北辰区","河北区","河西区","西青区","津南区","东丽区","武清区","宝坻区","红桥区","大港区","汉沽区","静海县","宁河县","塘沽区","蓟县","南开区","河东区","","","","","","","", "","","","","","","","","","","","","","","",\
	"江北区", "渝北区", "沙坪坝区", "九龙坡区", "万州区", "永川市", "南岸区", "酉阳县", "北碚区", "涪陵区", "秀山县", "巴南区", "渝中区", "石柱县", "忠县", "合川市", "大渡口区", "开县", "长寿区", "荣昌县", "云阳县", "梁平县", "潼南县", "江津市", "彭水县", "璧山县", "綦江县", "大足县", "黔江区", "巫溪县", "巫山县", "垫江县", "丰都县", "武隆县", "万盛区", "铜梁县", "南川市", "奉节县", "双桥区", "城口县"
};
string provs[23] = { "河北省", "山西省", "辽宁省", "吉林省", "黑龙江省", \
	"江苏省", "浙江省", "安徽省", "福建省", "江西省", "山东省", "河南省",\
	"湖北省", "湖南省", "广东省", "海南省", "四川省", "贵州省", "云南省",\
	"陕西省", "甘肃省", "青海省", "台湾省" };									//全国各省
string cities[23][30] =
{ "石家庄市","唐山市","保定市","邯郸市","邢台市","河北区","沧州市","秦皇岛市","张家口市","衡水市","廊坊市","承德市","","","","","","","","","","","","","","","","","","",\
   "太原市","大同市","运城市","长治市","晋城市","忻州市","临汾市","吕梁市","晋中市","阳泉市","朔州市","","","","","","","","","","","","","","","","","","","",\
   "大连市","沈阳市","丹东市","辽阳市","葫芦岛市","锦州市","朝阳市","营口市","鞍山市","抚顺市","阜新市","本溪市"," 盘锦市","铁岭市","","","","","","","","","","","","","","","","",\
	"吉林市","长春市","白山市","白城市","延边州","松原市","辽源市","通化市","四平市","","","","","","","","","","","","","","","","","","","","","",\
	"齐齐哈尔市","哈尔滨市","大庆市","佳木斯市","双鸭山市","牡丹江市","鸡西市","黑河市","绥化市","鹤岗市","伊春市","大兴安岭地区","七台河市","","","","","","","","","","","","","","","","","",\
	"苏州市","徐州市","盐城市","无锡市","南京市","南通市","连云港市","常州市","扬州市","镇江市","淮安市","泰州市"," 宿迁市","","","","","","","","","","","","","","","","","",\
	"温州市","宁波市","杭州市","台州市","嘉兴市","金华市","湖州市","绍兴市","舟山市","丽水市","衢州市","","","","","","","","","","","","","","","","","","","",\
	"芜湖市","合肥市","六安市","宿州市","阜阳市","安庆市","马鞍山市","蚌埠市","淮北市","淮南市","宣城市","黄山市"," 铜陵市","亳州市","池州市","巢湖市","滁州市","","","","","","","","","","","","","",\
	"漳州市","泉州市","厦门市","福州市","莆田市","宁德市","三明市","南平市","龙岩市","","","","","","","","","","","","","","","","","","","","","",\
	"南昌市","赣州市","上饶市","吉安市","九江市","新余市","抚州市","宜春市","景德镇市","萍乡市","鹰潭市","","","","","","","","","","","","","","","","","","","",\
	"济南市","青岛市","临沂市","济宁市","菏泽市","烟台市","泰安市","淄博市","潍坊市","日照市","威海市","滨州市","东营市","聊城市","德州市","莱芜市","枣庄市","","","","","","","","","","","","","",\
	"郑州市","南阳市","新乡市","安阳市","洛阳市","信阳市","平顶山市","周口市","商丘市","开封市","焦作市","驻马店市","濮阳市","三门峡市","漯河市","许昌市","鹤壁市","济源市","","","","","","","","","","","","",\
	"武汉市","宜昌市","襄樊市","荆州市","恩施州","孝感市","黄冈市","十堰市","咸宁市","黄石市","仙桃市","随州市","天门市","荆门市","潜江市","鄂州市","神农架林区","","","","","","","","","","","","","",\
	"长沙市","邵阳市","常德市","衡阳市","株洲市","湘潭市","永州市","岳阳市","怀化市","郴州市","娄底市","益阳市","张家界市","湘西州","","","","","","","","","","","","","","","","",""\
	"东莞市","广州市","中山市","深圳市","惠州市","江门市","珠海市","汕头市","佛山市","湛江市","河源市","肇庆市","潮州市","清远市","韶关市","揭阳市","阳江市","云浮市","茂名市","梅州市","汕尾市","","","","","","","","","",\
	"三亚市","海口市","琼海市","文昌市","东方市","昌江县","陵水县","乐东县","五指山市","保亭县","澄迈县","万宁市","儋州市","临高县","白沙县","定安县","琼中县","屯昌县","","","","","","","","","","","","",\
	"成都市","绵阳市","广元市","达州市","南充市","德阳市","广安市","阿坝州","巴中市","遂宁市","内江市","凉山州","攀枝花市","乐山市","自贡市","泸州市","雅安市","宜宾市","资阳市","眉山市","甘孜州","","","","","","","","","",\
	"贵阳市","黔东南州","黔南州","遵义市","黔西南州","毕节地区","铜仁地区","安顺市","六盘水市","","","","","","","","","","","","","","","","","","","","","",\
	"昆明市","红河州","大理州","文山州","德宏州","曲靖市","昭通市","楚雄州","保山市","玉溪市","丽江地区","临沧地区","思茅地区","西双版纳州","怒江州","迪庆州","","","","","","","","","","","","","","",\
	"西安市","咸阳市","宝鸡市","汉中市","渭南市","安康市","榆林市","商洛市","延安市","铜川市","","","","","","","","","","","","","","","","","","","","",\
	"兰州市","天水市","庆阳市","武威市","酒泉市","张掖市","陇南地区","白银市","定西地区","平凉市","嘉峪关市","临夏回族自治州","金昌市","甘南州","","","","","","","","","","","","","","","","",\
	"西宁市","海西州","海东地区","海北州","果洛州","玉树州","黄南藏族自治州","","","","","","","","","","","","","","","","","","","","","","","",\
	"台北市","高雄市","台中市","新竹市","基隆市","台南市","嘉义市","","","","","","","","","","","","","","","","","","","","","","",""\
};
string zzq[5] = { "广西壮族自治区","内蒙古自治区","新疆维吾尔自治区","宁夏回族自治区","西藏自治区" };//自治区
string zzq_cities[5][18] = {
	"贵港市","玉林市","北海市","南宁市","柳州市","桂林市","梧州市","钦州市","来宾市","河池市","百色市","贺州市","崇左市","防城港市","","","","",\
	"赤峰市", "包头市", "通辽市", "呼和浩特市", "乌海市", "鄂尔多斯市", "呼伦贝尔市", "兴安盟", "巴彦淖尔盟", "乌兰察布盟", "锡林郭勒盟", "阿拉善盟", "", "", "", "", "", "",\
	"乌鲁木齐市", "伊犁州", "昌吉州", "石河子市", "哈密地区", "阿克苏地区", "巴音郭楞州", "喀什地区", "塔城地区", "克拉玛依市", "和田地区", "阿勒泰州", "吐鲁番地区", "阿拉尔市", "博尔塔拉州", "五家渠市", "克孜勒苏州", "图木舒克市",\
	"银川市", "吴忠市", "中卫市", "石嘴山市", "固原市", "", "", "", "", "", "", "", "", "", "", "", "", "",\
	"拉萨市", "山南地区", "林芝地区", "日喀则地区", "阿里地区", "昌都地区", "那曲地区", "", "", "", "", "", "", "", "", "", ""
};//自治区城市

string type_seperate()			//地址类型解析
{
	regex r("^\\d!");
	smatch t;
	regex_search(addr, t, r);
	string type = t.str();
	addr = regex_replace(addr, r, "");
	/*string type;
	type = addr.substr(0, 1);
	addr.replace(0, 2, "");
	*/
	return type;
}

string name_seperate() //解析姓名
{
	int flag = addr.find(',');
	string name = addr.substr(0, flag);
	addr.replace(0, flag, "");	//解析出姓名后将姓名擦去
	addr.erase(addr.find("."), 1); //擦去 '.'
	addr.erase(addr.find(","), 1); //擦去 ','
	return name;
}

string Tel_num_analysis()//提取11位电话号码
{
	smatch t;
	regex r("\\d{11}");
	regex_search(addr, t, r);
	string Tel_number = t.str();
	addr = regex_replace(addr, r, "");

	return Tel_number;
};

class Five_addr_analysis		//五位地址解析
{
public:
	string name, tel_number, pro, Cities, country, town, detail_addr;
	int prov_tag;	//省份对应下标
	Five_addr_analysis(string Name, string Tel_num)
	{
		prov_tag = 0;
		name = Name;
		tel_number = Tel_num;
		pro = Cities = country = town = detail_addr = "";
	}
	void provs_seperate()//解析省
	{
		int flag;
		for (int i = 0; i < 23; i++)
		{
			/*地址中带"省"*/
			string temp = provs[i].substr(0, provs[i].size() - 2); //提取省份名称，例如：福建
			if ((flag = addr.find(provs[i])) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, provs[i].size()); //擦去“省”
				return;
			}
			/*地址中不带"省"的省*/
			else if ((flag = addr.find(temp)) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, temp.size()); //擦去“省”
				return;
			}

			/*直辖市、自治区前四个*/
			if (i < 4)
			{
				/*直辖市*/
				if ((flag = addr.find(direct_city[i])) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, direct_city[i].size());
					prov_tag = i + 23;//区分直辖市
					return;
				}
				temp = direct_city[i].substr(0, direct_city[i].size() - 2);//提取直辖市名称,例如：北京
				if ((flag = addr.find(temp)) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 23;//区分直辖市
					return;
				}

				/*自治区*/
				if ((flag = addr.find(zzq[i])) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, zzq[i].size());
					prov_tag = i + 27;//区分自治区
					return;
				}
				temp = zzq[i].substr(0, zzq[i].size() - 6);//提取自治区名字如内蒙古
				if ((flag = addr.find(temp)) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 27;//区分直辖市
					return;
				}
			}

			/*自治区*/
			if (i == 4)
			{
				if ((flag = addr.find(zzq[i])) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, zzq[i].size());
					prov_tag = i + 27;//区分自治区
					return;
				}
				temp = zzq[i].substr(0, zzq[i].size() - 6);//提取自治区名字西藏
				if ((flag = addr.find(temp)) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 27;//区分直辖市
					return;
				}
			}
		}
	}
	void cities_seperate()//解析市
	{
		int flag;
		if (prov_tag < 23) //一般城市
		{
			for (int i = 0; i < 30; i++)
			{
				if ((flag = addr.find(cities[prov_tag][i])) != -1)
				{
					Cities = cities[prov_tag][i];
					addr.erase(flag, cities[prov_tag][i].size()); //擦去“市”
					return;
				}
				/*地址中不带"市"*/
				else
				{
					string temp = cities[prov_tag][i].substr(0, cities[prov_tag][i].size() - 2);
					if ((flag = addr.find(temp)) != -1)
					{
						Cities = cities[prov_tag][i];
						addr.erase(flag, temp.size()); //擦去“市”
						return;
					}
				}
			}
		}
		else if (prov_tag < 27)//直辖市下的城市
		{
			prov_tag -= 23;
			for (int j = 0; j < 40; j++)
			{
				if ((flag = addr.find(direct_cities[prov_tag][j])) != -1)
				{
					Cities = direct_cities[prov_tag][j];
					addr.erase(flag, Cities.size());
					return;
				}
				string t = direct_cities[prov_tag][j].substr(0, direct_cities[prov_tag][j].size() - 2);
				if ((flag = addr.find(t)) != -1)
				{
					Cities = direct_cities[prov_tag][j];
					addr.erase(flag, t.size());
					return;
				}
			}
		}
		else//自治区下的城市
		{
			prov_tag -= 27;
			for (int j = 0; j < 18; j++)
			{
				if ((flag = addr.find(zzq_cities[prov_tag][j])) != -1)
				{
					Cities = zzq_cities[prov_tag][j];
					addr.erase(flag, Cities.size());
					return;
				}
				string t = zzq_cities[prov_tag][j].substr(0, zzq_cities[prov_tag][j].size() - 2);
				if ((flag = addr.find(t)) != -1)
				{
					Cities = zzq_cities[prov_tag][j];
					addr.erase(flag, t.size());
					return;
				}
				t = zzq_cities[prov_tag][j].substr(0, zzq_cities[prov_tag][j].size() - 4);
				if ((flag = addr.find(t)) != -1)
				{
					Cities = zzq_cities[prov_tag][j];
					addr.erase(flag, t.size());
					return;
				}
			}
		}
	}
	void counties_seperate()//解析县/区/县级市
	{
		regex r(".*?(区|县|市)");
		smatch Country;
		regex_search(addr, Country, r);//解析到县/区/县级市
		country += Country.str();
		addr = regex_replace(addr, r, "");
	}
	void towns_seperate()//解析街道/镇/乡
	{
		regex r(".+((街道)|镇|乡)");
		smatch Town;
		regex_search(addr, Town, r);//解析到街道/乡/镇
		town = Town.str();		//保存到town中
		addr = regex_replace(addr, r, "");
		return;
	}
	void detail_seperate()//解析 详细地址
	{
		detail_addr = addr;
	}
	void info_collect()//地址解析函数
	{
		provs_seperate();
		cities_seperate();
		counties_seperate();
		towns_seperate();
		detail_seperate();
	}
	string print_info()	//五级地址格式输出
	{
		string address = "{\"姓名\":\"" + name + "\",\"手机\":\"" + tel_number + "\",\"地址\":[" + "\"" + pro + "\",\"" + Cities + "\",\""
			+ country + "\",\"" + town + "\",\"" + detail_addr + "\"]}";
		//cout << address << endl;
		return address;
	}
};

class Seven_addr_analysis :public Five_addr_analysis
{
public:
	string road, gate_num;
	Seven_addr_analysis(string name, string tel_number) :Five_addr_analysis(name, tel_number) { road = gate_num = ""; }
	void road_seperate()//解析路
	{
		regex r(".+(路|街|巷|(胡同)|里)");
		smatch Road;
		regex_search(addr, Road, r);
		road = Road.str();
		addr = regex_replace(addr, r, "");
		return;
	}
	void gate_number()//解析门牌号
	{
		regex r(".+(号)");
		smatch gate;
		regex_search(addr, gate, r);
		gate_num = gate.str();
		addr = regex_replace(addr, r, "");
		return;
	}
	void provs_seperate()	//解析省
	{
		int flag;
		for (int i = 0; i < 23; i++)
		{
			/*地址中带"省"*/
			string temp = provs[i].substr(0, provs[i].size() - 2); //提取省份名称，例如：福建
			if ((flag = addr.find(provs[i])) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, provs[i].size()); //擦去“省”
				return;
			}
			/*地址中不带"省"的省*/
			else if ((flag = addr.find(temp)) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, temp.size()); //擦去“省”
				return;
			}
			/*直辖市*/
			if (i < 4)
			{
				//temp = direct_city[i].substr(0, direct_city[i].size() - 2);//匹配直辖市全称
				if ((flag = addr.find(direct_city[i])) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, direct_city[i].size());
					prov_tag = i + 23;//区分直辖市
					return;
				}
			}
		}
	}
	void info_collect()//提取地图信息
	{
		provs_seperate();
		cities_seperate();
		counties_seperate();
		towns_seperate();
		road_seperate();
		gate_number();
		detail_seperate();
	}
	string print_info()//七级地址格式输出
	{
		string address = "{\"姓名\":\"" + name + "\",\"手机\":\"" + tel_number + "\",\"地址\":[" + "\"" + pro + "\",\"" + Cities + "\",\""
			+ country + "\",\"" + town + "\",\"" + road + "\",\"" + gate_num + "\",\"" + detail_addr + "\"]}";
		//cout << address << endl;
		return address;
	}
};


int main(int argc, char **argv)
{
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);
	vector<string> address;
	int count = 0;
	string s;
	output << "[" << endl;
	while (getline(input, s))
	{
		address.push_back(s);
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		addr = address[i];
		string type = type_seperate();
		string name = name_seperate();
		string tel_number = Tel_num_analysis();

		if (type == "1!")
		{
			Five_addr_analysis add_analysis(name, tel_number); //创建五级地址对象
			add_analysis.info_collect();
			string info = add_analysis.print_info();
			/*wstring t = utf8string2wstring(info);
			info = wstring2string(t, "Chinese");*/
			//写入文件
			if (i != count - 1)
			{
				info += ",";
				output << info << endl;
			}
			else
				output << info << endl;
		}
		else if (type == "2!")
		{
			Seven_addr_analysis add_analysis(name, tel_number);//创建七级地址对象
			add_analysis.info_collect();
			string info = add_analysis.print_info();
			//写入文件
			if (i != count - 1)
			{
				info += ",";
				output << info << endl;
			}
			else
				output << info << endl;
		}
		/*else if (type == "3!")
		{
			output << "Cant' deal with case 3!" << endl;
		}
		else
		{
			output << "Type Wrong!" << endl;
		}*/
	}
	output << "]" << endl;
	input.close();
	output.close();

		/*ifstream f("F:\\VS project\\test_date.txt");
		ofstream o("F:\\VS project\\test_result_date.txt");
		while (getline(f, addr))
		{
			string type = type_seperate();
			string name = name_seperate();
			string tel_number = Tel_num_analysis();

			if (type == "1!")
			{
				Five_addr_analysis add_analysis(name, tel_number); //创建五级地址对象
				add_analysis.info_collect();
				add_analysis.print_info();
			}
			else if (type == "2!" || type == "3!")
			{
				Seven_addr_analysis add_analysis(name, tel_number);//创建七级地址对象
				add_analysis.info_collect();
				add_analysis.print_info();
			}

		}
		f.close();
		system("pause");
		*/
		return 0;
}
