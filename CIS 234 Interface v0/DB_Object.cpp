//#include <my_global.h>
//#include "mysql.h"
//#include <stdio.h> 
//
//
//
//#pragma comment(lib, "libmysql")
//#pragma comment(lib, "mysqlclient")
//
//int main(){ 
//
//	MYSQL mysql; 
//	MYSQL_ROW row; 
//	MYSQL_RES *result; 
//
//	unsigned int num_fields; 
//	unsigned int i; 
//	const short PORT = 3306;
//
//	mysql_init(&mysql); 
//
//	if (!mysql_real_connect(&mysql,"localhost","root","root","mydb",PORT,NULL,NULL)) 
//	{ 
//		fprintf(stderr, "Failed to connect to database: Error: %s\n", 
//			mysql_error(&mysql)); 
//	} 
//	else
//	{ 
//		if(mysql_query(&mysql, "SELECT * FROM divisions")); 
//		//here goes the error message :o) 
//		else { 
//			result = mysql_store_result(&mysql); 
//			num_fields = mysql_num_fields(result); 
//			while ((row = mysql_fetch_row(result))) 
//			{ 
//				unsigned long *lengths; 
//				lengths = mysql_fetch_lengths(result); 
//				for(i = 0; i < num_fields; i++) 
//				{ 
//					printf("[%.*s] \t", (int) lengths[i], row[i] ? row[i] : "NULL"); 
//				}    
//				printf("\n"); 
//			} 
//		} 
//	} 
//
//	printf("\n"); 
//
//	return 0; 
//
//} 
////
////
////using System;
////using System.Collections.Generic;
////using System.Linq;
////using System.Text;
////using System.Data.SqlClient;
////using System.Data;
////using System.Windows.Forms;
////
////namespace KenoKS
////{
////    public class DBClass
////    {
////        public static SqlConnection MainSqlConnection;
////
////        public static void setup(String SellpointID)
////        {
////            if (MainSqlConnection != null)
////            {
////                SqlConnectionStringBuilder conn = new SqlConnectionStringBuilder(MainSqlConnection.ConnectionString) { ConnectTimeout = 5, InitialCatalog = "" + SellpointID }; // you can add other parameters.
////                MainSqlConnection.ConnectionString = conn.ConnectionString;
////
////            }
////        }
////        public static bool FillDataSet(DataSet ds, string CommandText)
////        {
////
////
////            bool result = false;
////            try
////            {
////                ds.Clear();
////                SqlDataAdapter da = new SqlDataAdapter(CommandText, MainSqlConnection);
////                if(MainSqlConnection.State != ConnectionState.Open)
////                {
////                    MainSqlConnection.Open();
////                }
////                try
////                {
////                    da.Fill(ds);
////                }
////                finally
////                {
////                    da.Dispose();
////                }
////                result = true;
////            }
////            catch (SqlException ex)
////            {
////                result = false;
////            }
////            return result;
////        }
////
////
////        public static bool ExecSql(string CommandText)
////        {
////            bool a = false;
////            SqlCommand cmd = new SqlCommand(CommandText, MainSqlConnection);
////            try
////            {
////                if (cmd.Connection.State != ConnectionState.Open)
////                    cmd.Connection.Open();
////                cmd.ExecuteNonQuery();
////                cmd.Connection.Close();
////                a = true;
////            }
////            catch (SqlException ex)
////            {
////
////
////                a = false;
////                if (ex.Number == 2601 || ex.Number == 2627)
////                {
////                    MessageBox.Show("Keni futur duplikat të ID Numrit në bazën e shënemieve." + (char)13 + "Modifikoni ID Numrin");
////                    return false;
////                }
////                else
////                    MessageBox.Show("Gabim ne ekzekutim:" + ex.Message);
////            }
////            finally
////            {
////                cmd.Dispose();
////            }
////            return a;
////        }
////
////        public static string ExecSqlScalar(string CommandText)
////        {
////            string a = "";
////
////            SqlCommand cmd = new SqlCommand(CommandText, MainSqlConnection);
////            try
////            {
////                if (cmd.Connection.State != ConnectionState.Open)
////                    cmd.Connection.Open();
////                a = cmd.ExecuteScalar().ToString();
////                cmd.Connection.Close();
////
////            }
////            catch (SqlException ex)
////            {
////                a = "error";
////                if (ex.Number == 2601 || ex.Number == 2627)
////                {
////                    MessageBox.Show("Keni futur duplikat të ID Numrit në bazën e shënemieve." + (char)13 + "Modifikoni ID Numrin");
////                }
////                else
////                    MessageBox.Show("Gabim ne ekzekutim:" + ex.Message);
////            }
////            finally
////            {
////                cmd.Dispose();
////            }
////            return a;
////        }
////    }
////}