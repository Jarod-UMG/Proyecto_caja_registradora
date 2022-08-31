using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using objWord = Microsoft.Office.Interop.Word;

namespace Imprimir_Productos
{
    public partial class Form1 : Form
    {
        protected static string ruta;
        protected static string rutaw;
        protected static string rutam;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ValoresIniciales();
        }
        protected void ValoresIniciales()
        {
            ruta = @"../../../../../Base de Datos/Productos.txt";
            rutam = @"../../../../../Base de Datos/Marcas.txt";
            rutaw = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            GenerarColumnas();
            GenerarListado();
            if (dgvlistado.Rows.Count <= 0)
            {
                MessageBox.Show("No se ha encontrado ningun registro");
            }
        }
        protected void GenerarListado()
        {
            using (StreamReader texto = new StreamReader(ruta))
            {
                while (!texto.EndOfStream)
                {
                    string x = texto.ReadLine();
                    if (string.IsNullOrEmpty(x)) { }
                    else
                    {

                        string[] contenido = x.Split(' ');
                        dgvlistado.Rows.Add(contenido[0], contenido[1],RetornarMarcas(contenido[2]), "Q" + contenido[3], "Q" + contenido[4], contenido[5], "0");

                    }

                }
            }

        }
        protected void GenerarColumnas()
        {
            DataGridViewTextBoxColumn textbox = new DataGridViewTextBoxColumn();
            textbox.HeaderText = "Cantidad";
            textbox.Width = 60;
            textbox.MaxInputLength = 1;

            DataGridViewTextBoxColumn producto = new DataGridViewTextBoxColumn();
            producto.HeaderText = "Producto";

            DataGridViewTextBoxColumn marca = new DataGridViewTextBoxColumn();
            marca.HeaderText = "Marca";

            DataGridViewTextBoxColumn precioc = new DataGridViewTextBoxColumn();
            precioc.HeaderText = "Precio de Compra";

            DataGridViewTextBoxColumn preciov = new DataGridViewTextBoxColumn();
            preciov.HeaderText = "Precio de Venta";

            DataGridViewTextBoxColumn codigo = new DataGridViewTextBoxColumn();
            codigo.HeaderText = "Codigo";

            DataGridViewTextBoxColumn fecha = new DataGridViewTextBoxColumn();
            fecha.HeaderText = "Fecha de Ingreso";

            dgvlistado.Columns.Add(codigo);
            dgvlistado.Columns.Add(producto);
            dgvlistado.Columns.Add(marca);
            dgvlistado.Columns.Add(precioc);
            dgvlistado.Columns.Add(preciov);
            dgvlistado.Columns.Add(fecha);
            dgvlistado.Columns.Add(textbox);
        }

        private void btngenerar_Click(object sender, EventArgs e)
        {
            string codigo, desc;
            if (dgvlistado.Rows.Count <= 0)
            {
                MessageBox.Show("No se ha encontrado ningun registro");
            }
            else
            {
                objWord.Application objAplicacion = new objWord.Application();
                objWord.Document objDocumento = objAplicacion.Documents.Add();
                for (int i = 0; i < dgvlistado.RowCount - 1; i++)
                {
                    codigo = dgvlistado.Rows[i].Cells[0].Value.ToString();
                    desc = dgvlistado.Rows[i].Cells[1].Value.ToString();
                    if (VeririficarCod(codigo))
                    {
                        objWord.Paragraph objParrafo = objDocumento.Content.Paragraphs.Add(Type.Missing);
                        objParrafo.Range.Font.Size = 14;
                        objParrafo.Range.Font.Color = objWord.WdColor.wdColorBlack;
                        objParrafo.Range.Text = codigo;
                        objParrafo.Range.Font.Name = "Code39";
                        objParrafo.Range.InsertParagraphAfter();
                    }
                    else
                    {
                        MessageBox.Show("No existe el codigo del producto");
                    }
                }
                objDocumento.SaveAs2(rutaw + "\\CodigoMarcas.docx");
                objDocumento.Close();
                objAplicacion.Quit();
            }
        }
        protected bool VeririficarCod(string codigo)
        {
            int conteo = 0;
            using (StreamReader texto = new StreamReader(ruta))
            {
                while (!texto.EndOfStream)
                {
                    string x = texto.ReadLine();
                    if (string.IsNullOrEmpty(x)) { }
                    else
                    {
                        string[] contenido = x.Split(' ');
                        if (codigo == contenido[0])
                        {
                            conteo++;
                        }
                    }

                }
            }
            if (conteo > 0)
            {
                return true;
            }
            else
            {
                return false;
            }

        }
        protected string RetornarMarcas(string codigo)
        {
            string des = "";
            int conteo = 0;
            using (StreamReader texto = new StreamReader(rutam))
            {
                while (!texto.EndOfStream)
                {
                    string x = texto.ReadLine();
                    if (string.IsNullOrEmpty(x)) { }
                    else
                    {
                        string[] contenido = x.Split(' ');
                        if (codigo == contenido[0])
                        {
                            des = contenido[1];
                            conteo++;
                        }
                    }
                }
            }
            if (conteo > 0)
            {
                return des;
            }
            else
            {
                return des;
            }
        }

        private void btnactualizarTabla_Click(object sender, EventArgs e)
        {
            dgvlistado.Rows.Clear();
            GenerarListado();
        }
    }
}
