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
using System.Reflection;
using System.Resources;
using System.Diagnostics;
using System.Management;

namespace Compiler
{
    public partial class Form1 : Form
    {
        //compilerCore.Manager compiler;
        bool srcChanged, fileSaved;
        String filePath;

        dynamic compilerDLLInstance;

        public Form1()
        {
            InitializeComponent();
            //compiler = new compilerCore.Manager();
            srcChanged = false;
            fileSaved = false;
            saveFileDialog1.Filter = "Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*";
            gridTokens.Columns.Add("Lex", "Lex");
            gridTokens.Columns.Add("Line", "Line");
            gridTokens.Columns.Add("Type", "Type");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string dllFullPath = "";

            if (System.Environment.Is64BitProcess) // 64 bits
            {
                if (processCanBeDebugged()) // Debug
                {
                    dllFullPath = Path.Combine(getPath(), "x64\\Debug");// obtener el path completo a la DLL compilada en x64/Debug
                }
                else // Release
                {
                    dllFullPath = Path.Combine(getPath(), "x64\\Release");// obtener el path completo a la DLL compilada en x64/Release
                }
            }
            else // 32bits
            {
                if (processCanBeDebugged()) // Debug
                {
                    dllFullPath = Path.Combine(getPath(), "x86\\Debug");// obtener el path completo a la DLL compilada en x86/Debug
                }
                else // Release
                {
                    dllFullPath = Path.Combine(getPath(), "x86\\Release");// obtener el path completo a la DLL compilada en x86/Release
                }
            }
            dllFullPath = Path.Combine(dllFullPath, "compilerCore.dll");
            var DLL = Assembly.LoadFile(dllFullPath);
            var DLLType = DLL.GetType("compilerCore.Manager");
            compilerDLLInstance = Activator.CreateInstance(DLLType);
            if (compilerDLLInstance != null)
            {

            }
        }

        private void compileProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtOutput.Clear();
            gridTokens.Rows.Clear();
            String[] compilationDetails = compilerDLLInstance.compileProgram(txtSrc.Text);
            for(int i=0;i<compilationDetails.Length;i++)
            {
                if(compilationDetails[i].Contains("<LEXIC_ANALYZER>"))
                {
                    txtOutput.Text += compilationDetails[i];
                    txtOutput.Text += "\r\n";
                }
                else
                {
                    String[] token = compilationDetails[i].Split('@');
                    int rowNum = gridTokens.Rows.Add();
                    gridTokens.Rows[rowNum].Cells[0].Value = token[0];
                    gridTokens.Rows[rowNum].Cells[2].Value = token[1];
                    gridTokens.Rows[rowNum].Cells[1].Value = token[2];
                }
            }
            gridTokens.AutoResizeColumns();
            gridTokens.AutoResizeRows();
            //txtOutput.Lines = compilationDetails;
        }

        private void txtSrc_TextChanged(object sender, EventArgs e)
        {
            if (!srcChanged)
            {
                srcChanged = true;
            }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (srcChanged)
            {
                if (MessageBox.Show("¿Desea guardar los cambios en el archivo?", "Advertencia", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (fileSaved)
                    {
                        save();
                    }
                    else
                    {
                        saveAs();
                    }
                }
            }
            reload();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (srcChanged)
            {
                if (MessageBox.Show("¿Desea guardar los cambios en el archivo?", "Advertencia", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (fileSaved)
                    {
                        save();
                    }
                    else
                    {
                        saveAs();
                    }
                }
            }
            open();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fileSaved)
            {
                save();
            }
            else
            {
                saveAs();
            }
        }

        private void sToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveAs();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (srcChanged)
            {
                if (MessageBox.Show("¿Desea guardar los cambios en el archivo?", "Advertencia", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (fileSaved)
                    {
                        save();
                    }
                    else
                    {
                        saveAs();
                    }
                }
            }
            this.Close();
        }

        private void reload()
        {
            txtSrc.ResetText();
            txtOutput.ResetText();
            srcChanged = false;
            fileSaved = false;
            gridSymbols.DataSource = null;
            gridTokens.DataSource = null;
        }

        private void open()
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                txtSrc.Text = File.ReadAllText(openFileDialog1.FileName);
                filePath = Path.GetFullPath(openFileDialog1.FileName);
                fileSaved = true;
                srcChanged = false;
            }
        }

        private void save()
        {
            File.WriteAllText(filePath, txtSrc.Text);
            srcChanged = false;
        }

        private void saveAs()
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(saveFileDialog1.FileName, txtSrc.Text);
                filePath = Path.GetFullPath(saveFileDialog1.FileName);
                fileSaved = true;
                srcChanged = false;
            }
        }

        private bool processCanBeDebugged()
        {
            object[] attribs = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(DebuggableAttribute), true);
            if ((attribs != null) && (attribs.Length == 1))
            {
                DebuggableAttribute attribute = attribs[0] as DebuggableAttribute;

                if (attribute.IsJITOptimizerDisabled && attribute.IsJITTrackingEnabled)
                {
                    return true;
                }
            }
            return false;
        }

        private string getPath()
        {
            string processFullPath = Application.StartupPath;
            for (int i = 0; i < 4; i++)
            {
                processFullPath = Directory.GetParent(processFullPath).ToString();
            }
            //var currentProcess = Process.GetCurrentProcess();
            //if (System.Environment.Is64BitProcess)
            //{
            //    processFullPath = currentProcess.MainModule.FileName;
            //    for (int i = 0; i < 5; i++)
            //        processFullPath = Directory.GetParent(processFullPath).ToString();
            //}
            //else
            //{
            //    processFullPath = Application.StartupPath;
            //}
            processFullPath = Path.Combine(processFullPath, "DLL\\Binaries\\");
            return processFullPath;
        }
    }
}
