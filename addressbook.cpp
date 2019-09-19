#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <regex>
using namespace std;

string addr;	//��ַ����
string direct_city[4] = { "������","�Ϻ���","�����","������" };//ֱϽ��
string direct_cities[4][40] = {
	"������","������","ͨ����","��ɽ��","��̨��","��ƽ��","������","˳����","������","������","ʯ��ɽ��","������","������","������","������","������","��ͷ����","ƽ����","","","","","","","",  "","","","","","","","","","","","","","","",\
	"�ɽ���","��ɽ��","��ɽ��","�ζ���","�ϻ���","������","�ֶ�����","������","������","�����","������","������","������","������","�����","բ����","������","������","¬����","","","","","","",  "","","","","","","","","","","","","","","",\
	"��ƽ��","������","�ӱ���","������","������","������","������","������","������","������","�����","������","������","������","������","����","�Ͽ���","�Ӷ���","","","","","","","", "","","","","","","","","","","","","","","",\
	"������", "�山��", "ɳƺ����", "��������", "������", "������", "�ϰ���", "������", "������", "������", "��ɽ��", "������", "������", "ʯ����", "����", "�ϴ���", "��ɿ���", "����", "������", "�ٲ���", "������", "��ƽ��", "������", "������", "��ˮ��", "�ɽ��", "�뽭��", "������", "ǭ����", "��Ϫ��", "��ɽ��", "�潭��", "�ᶼ��", "��¡��", "��ʢ��", "ͭ����", "�ϴ���", "�����", "˫����", "�ǿ���"
};
string provs[23] = { "�ӱ�ʡ", "ɽ��ʡ", "����ʡ", "����ʡ", "������ʡ", \
	"����ʡ", "�㽭ʡ", "����ʡ", "����ʡ", "����ʡ", "ɽ��ʡ", "����ʡ",\
	"����ʡ", "����ʡ", "�㶫ʡ", "����ʡ", "�Ĵ�ʡ", "����ʡ", "����ʡ",\
	"����ʡ", "����ʡ", "�ຣʡ", "̨��ʡ" };									//ȫ����ʡ
string cities[23][30] =
{ "ʯ��ׯ��","��ɽ��","������","������","��̨��","�ӱ���","������","�ػʵ���","�żҿ���","��ˮ��","�ȷ���","�е���","","","","","","","","","","","","","","","","","","",\
   "̫ԭ��","��ͬ��","�˳���","������","������","������","�ٷ���","������","������","��Ȫ��","˷����","","","","","","","","","","","","","","","","","","","",\
   "������","������","������","������","��«����","������","������","Ӫ����","��ɽ��","��˳��","������","��Ϫ��"," �̽���","������","","","","","","","","","","","","","","","","",\
	"������","������","��ɽ��","�׳���","�ӱ���","��ԭ��","��Դ��","ͨ����","��ƽ��","","","","","","","","","","","","","","","","","","","","","",\
	"���������","��������","������","��ľ˹��","˫Ѽɽ��","ĵ������","������","�ں���","�绯��","�׸���","������","���˰������","��̨����","","","","","","","","","","","","","","","","","",\
	"������","������","�γ���","������","�Ͼ���","��ͨ��","���Ƹ���","������","������","����","������","̩����"," ��Ǩ��","","","","","","","","","","","","","","","","","",\
	"������","������","������","̨����","������","����","������","������","��ɽ��","��ˮ��","������","","","","","","","","","","","","","","","","","","","",\
	"�ߺ���","�Ϸ���","������","������","������","������","��ɽ��","������","������","������","������","��ɽ��"," ͭ����","������","������","������","������","","","","","","","","","","","","","",\
	"������","Ȫ����","������","������","������","������","������","��ƽ��","������","","","","","","","","","","","","","","","","","","","","","",\
	"�ϲ���","������","������","������","�Ž���","������","������","�˴���","��������","Ƽ����","ӥ̶��","","","","","","","","","","","","","","","","","","","",\
	"������","�ൺ��","������","������","������","��̨��","̩����","�Ͳ���","Ϋ����","������","������","������","��Ӫ��","�ĳ���","������","������","��ׯ��","","","","","","","","","","","","","",\
	"֣����","������","������","������","������","������","ƽ��ɽ��","�ܿ���","������","������","������","פ�����","�����","����Ͽ��","�����","�����","�ױ���","��Դ��","","","","","","","","","","","","",\
	"�人��","�˲���","�差��","������","��ʩ��","Т����","�Ƹ���","ʮ����","������","��ʯ��","������","������","������","������","Ǳ����","������","��ũ������","","","","","","","","","","","","","",\
	"��ɳ��","������","������","������","������","��̶��","������","������","������","������","¦����","������","�żҽ���","������","","","","","","","","","","","","","","","","",""\
	"��ݸ��","������","��ɽ��","������","������","������","�麣��","��ͷ��","��ɽ��","տ����","��Դ��","������","������","��Զ��","�ع���","������","������","�Ƹ���","ï����","÷����","��β��","","","","","","","","","",\
	"������","������","����","�Ĳ���","������","������","��ˮ��","�ֶ���","��ָɽ��","��ͤ��","������","������","������","�ٸ���","��ɳ��","������","������","�Ͳ���","","","","","","","","","","","","",\
	"�ɶ���","������","��Ԫ��","������","�ϳ���","������","�㰲��","������","������","������","�ڽ���","��ɽ��","��֦����","��ɽ��","�Թ���","������","�Ű���","�˱���","������","üɽ��","������","","","","","","","","","",\
	"������","ǭ������","ǭ����","������","ǭ������","�Ͻڵ���","ͭ�ʵ���","��˳��","����ˮ��","","","","","","","","","","","","","","","","","","","","","",\
	"������","�����","������","��ɽ��","�º���","������","��ͨ��","������","��ɽ��","��Ϫ��","��������","�ٲ׵���","˼é����","��˫������","ŭ����","������","","","","","","","","","","","","","","",\
	"������","������","������","������","μ����","������","������","������","�Ӱ���","ͭ����","","","","","","","","","","","","","","","","","","","","",\
	"������","��ˮ��","������","������","��Ȫ��","��Ҵ��","¤�ϵ���","������","��������","ƽ����","��������","���Ļ���������","�����","������","","","","","","","","","","","","","","","","",\
	"������","������","��������","������","������","������","���ϲ���������","","","","","","","","","","","","","","","","","","","","","","","",\
	"̨����","������","̨����","������","��¡��","̨����","������","","","","","","","","","","","","","","","","","","","","","","",""\
};
string zzq[5] = { "����׳��������","���ɹ�������","�½�ά���������","���Ļ���������","����������" };//������
string zzq_cities[5][18] = {
	"�����","������","������","������","������","������","������","������","������","�ӳ���","��ɫ��","������","������","���Ǹ���","","","","",\
	"�����", "��ͷ��", "ͨ����", "���ͺ�����", "�ں���", "������˹��", "���ױ�����", "�˰���", "�����׶���", "�����첼��", "���ֹ�����", "��������", "", "", "", "", "", "",\
	"��³ľ����", "������", "������", "ʯ������", "���ܵ���", "�����յ���", "����������", "��ʲ����", "���ǵ���", "����������", "�������", "����̩��", "��³������", "��������", "����������", "�������", "����������", "ͼľ�����",\
	"������", "������", "������", "ʯ��ɽ��", "��ԭ��", "", "", "", "", "", "", "", "", "", "", "", "", "",\
	"������", "ɽ�ϵ���", "��֥����", "�տ������", "�������", "��������", "��������", "", "", "", "", "", "", "", "", "", ""
};//����������

string type_seperate()			//��ַ���ͽ���
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

string name_seperate() //��������
{
	int flag = addr.find(',');
	string name = addr.substr(0, flag);
	addr.replace(0, flag, "");	//������������������ȥ
	addr.erase(addr.find("."), 1); //��ȥ '.'
	addr.erase(addr.find(","), 1); //��ȥ ','
	return name;
}

string Tel_num_analysis()//��ȡ11λ�绰����
{
	smatch t;
	regex r("\\d{11}");
	regex_search(addr, t, r);
	string Tel_number = t.str();
	addr = regex_replace(addr, r, "");

	return Tel_number;
};

class Five_addr_analysis		//��λ��ַ����
{
public:
	string name, tel_number, pro, Cities, country, town, detail_addr;
	int prov_tag;	//ʡ�ݶ�Ӧ�±�
	Five_addr_analysis(string Name, string Tel_num)
	{
		prov_tag = 0;
		name = Name;
		tel_number = Tel_num;
		pro = Cities = country = town = detail_addr = "";
	}
	void provs_seperate()//����ʡ
	{
		int flag;
		for (int i = 0; i < 23; i++)
		{
			/*��ַ�д�"ʡ"*/
			string temp = provs[i].substr(0, provs[i].size() - 2); //��ȡʡ�����ƣ����磺����
			if ((flag = addr.find(provs[i])) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, provs[i].size()); //��ȥ��ʡ��
				return;
			}
			/*��ַ�в���"ʡ"��ʡ*/
			else if ((flag = addr.find(temp)) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, temp.size()); //��ȥ��ʡ��
				return;
			}

			/*ֱϽ�С�������ǰ�ĸ�*/
			if (i < 4)
			{
				/*ֱϽ��*/
				if ((flag = addr.find(direct_city[i])) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, direct_city[i].size());
					prov_tag = i + 23;//����ֱϽ��
					return;
				}
				temp = direct_city[i].substr(0, direct_city[i].size() - 2);//��ȡֱϽ������,���磺����
				if ((flag = addr.find(temp)) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 23;//����ֱϽ��
					return;
				}

				/*������*/
				if ((flag = addr.find(zzq[i])) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, zzq[i].size());
					prov_tag = i + 27;//����������
					return;
				}
				temp = zzq[i].substr(0, zzq[i].size() - 6);//��ȡ���������������ɹ�
				if ((flag = addr.find(temp)) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 27;//����ֱϽ��
					return;
				}
			}

			/*������*/
			if (i == 4)
			{
				if ((flag = addr.find(zzq[i])) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, zzq[i].size());
					prov_tag = i + 27;//����������
					return;
				}
				temp = zzq[i].substr(0, zzq[i].size() - 6);//��ȡ��������������
				if ((flag = addr.find(temp)) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 27;//����ֱϽ��
					return;
				}
			}
		}
	}
	void cities_seperate()//������
	{
		int flag;
		if (prov_tag < 23) //һ�����
		{
			for (int i = 0; i < 30; i++)
			{
				if ((flag = addr.find(cities[prov_tag][i])) != -1)
				{
					Cities = cities[prov_tag][i];
					addr.erase(flag, cities[prov_tag][i].size()); //��ȥ���С�
					return;
				}
				/*��ַ�в���"��"*/
				else
				{
					string temp = cities[prov_tag][i].substr(0, cities[prov_tag][i].size() - 2);
					if ((flag = addr.find(temp)) != -1)
					{
						Cities = cities[prov_tag][i];
						addr.erase(flag, temp.size()); //��ȥ���С�
						return;
					}
				}
			}
		}
		else if (prov_tag < 27)//ֱϽ���µĳ���
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
		else//�������µĳ���
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
	void counties_seperate()//������/��/�ؼ���
	{
		regex r(".*?(��|��|��)");
		smatch Country;
		regex_search(addr, Country, r);//��������/��/�ؼ���
		country += Country.str();
		addr = regex_replace(addr, r, "");
	}
	void towns_seperate()//�����ֵ�/��/��
	{
		regex r(".+((�ֵ�)|��|��)");
		smatch Town;
		regex_search(addr, Town, r);//�������ֵ�/��/��
		town = Town.str();		//���浽town��
		addr = regex_replace(addr, r, "");
		return;
	}
	void detail_seperate()//���� ��ϸ��ַ
	{
		detail_addr = addr;
	}
	void info_collect()//��ַ��������
	{
		provs_seperate();
		cities_seperate();
		counties_seperate();
		towns_seperate();
		detail_seperate();
	}
	string print_info()	//�弶��ַ��ʽ���
	{
		string address = "{\"����\":\"" + name + "\",\"�ֻ�\":\"" + tel_number + "\",\"��ַ\":[" + "\"" + pro + "\",\"" + Cities + "\",\""
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
	void road_seperate()//����·
	{
		regex r(".+(·|��|��|(��ͬ)|��)");
		smatch Road;
		regex_search(addr, Road, r);
		road = Road.str();
		addr = regex_replace(addr, r, "");
		return;
	}
	void gate_number()//�������ƺ�
	{
		regex r(".+(��)");
		smatch gate;
		regex_search(addr, gate, r);
		gate_num = gate.str();
		addr = regex_replace(addr, r, "");
		return;
	}
	void provs_seperate()	//����ʡ
	{
		int flag;
		for (int i = 0; i < 23; i++)
		{
			/*��ַ�д�"ʡ"*/
			string temp = provs[i].substr(0, provs[i].size() - 2); //��ȡʡ�����ƣ����磺����
			if ((flag = addr.find(provs[i])) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, provs[i].size()); //��ȥ��ʡ��
				return;
			}
			/*��ַ�в���"ʡ"��ʡ*/
			else if ((flag = addr.find(temp)) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, temp.size()); //��ȥ��ʡ��
				return;
			}
			/*ֱϽ��*/
			if (i < 4)
			{
				//temp = direct_city[i].substr(0, direct_city[i].size() - 2);//ƥ��ֱϽ��ȫ��
				if ((flag = addr.find(direct_city[i])) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, direct_city[i].size());
					prov_tag = i + 23;//����ֱϽ��
					return;
				}
			}
		}
	}
	void info_collect()//��ȡ��ͼ��Ϣ
	{
		provs_seperate();
		cities_seperate();
		counties_seperate();
		towns_seperate();
		road_seperate();
		gate_number();
		detail_seperate();
	}
	string print_info()//�߼���ַ��ʽ���
	{
		string address = "{\"����\":\"" + name + "\",\"�ֻ�\":\"" + tel_number + "\",\"��ַ\":[" + "\"" + pro + "\",\"" + Cities + "\",\""
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
			Five_addr_analysis add_analysis(name, tel_number); //�����弶��ַ����
			add_analysis.info_collect();
			string info = add_analysis.print_info();
			/*wstring t = utf8string2wstring(info);
			info = wstring2string(t, "Chinese");*/
			//д���ļ�
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
			Seven_addr_analysis add_analysis(name, tel_number);//�����߼���ַ����
			add_analysis.info_collect();
			string info = add_analysis.print_info();
			//д���ļ�
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
				Five_addr_analysis add_analysis(name, tel_number); //�����弶��ַ����
				add_analysis.info_collect();
				add_analysis.print_info();
			}
			else if (type == "2!" || type == "3!")
			{
				Seven_addr_analysis add_analysis(name, tel_number);//�����߼���ַ����
				add_analysis.info_collect();
				add_analysis.print_info();
			}

		}
		f.close();
		system("pause");
		*/
		return 0;
}
