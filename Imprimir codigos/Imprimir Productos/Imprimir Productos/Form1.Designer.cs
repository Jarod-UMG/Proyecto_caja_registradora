namespace Imprimir_Productos
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.dgvlistado = new System.Windows.Forms.DataGridView();
            this.lbltextoinfo = new System.Windows.Forms.Label();
            this.lbltitulo = new System.Windows.Forms.Label();
            this.btngenerar = new System.Windows.Forms.Button();
            this.btnactualizarTabla = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvlistado)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvlistado
            // 
            this.dgvlistado.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvlistado.Location = new System.Drawing.Point(114, 195);
            this.dgvlistado.Name = "dgvlistado";
            this.dgvlistado.Size = new System.Drawing.Size(621, 278);
            this.dgvlistado.TabIndex = 0;
            // 
            // lbltextoinfo
            // 
            this.lbltextoinfo.AutoSize = true;
            this.lbltextoinfo.Location = new System.Drawing.Point(393, 124);
            this.lbltextoinfo.Name = "lbltextoinfo";
            this.lbltextoinfo.Size = new System.Drawing.Size(0, 13);
            this.lbltextoinfo.TabIndex = 1;
            // 
            // lbltitulo
            // 
            this.lbltitulo.AutoSize = true;
            this.lbltitulo.Location = new System.Drawing.Point(393, 59);
            this.lbltitulo.Name = "lbltitulo";
            this.lbltitulo.Size = new System.Drawing.Size(0, 13);
            this.lbltitulo.TabIndex = 2;
            // 
            // btngenerar
            // 
            this.btngenerar.Location = new System.Drawing.Point(379, 166);
            this.btngenerar.Name = "btngenerar";
            this.btngenerar.Size = new System.Drawing.Size(120, 23);
            this.btngenerar.TabIndex = 3;
            this.btngenerar.Text = "Generar Archivo";
            this.btngenerar.UseVisualStyleBackColor = true;
            this.btngenerar.Click += new System.EventHandler(this.btngenerar_Click);
            // 
            // btnactualizarTabla
            // 
            this.btnactualizarTabla.Location = new System.Drawing.Point(505, 166);
            this.btnactualizarTabla.Name = "btnactualizarTabla";
            this.btnactualizarTabla.Size = new System.Drawing.Size(120, 23);
            this.btnactualizarTabla.TabIndex = 4;
            this.btnactualizarTabla.Text = "Actualizar Tabla";
            this.btnactualizarTabla.UseVisualStyleBackColor = true;
            this.btnactualizarTabla.Click += new System.EventHandler(this.btnactualizarTabla_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(867, 542);
            this.Controls.Add(this.btnactualizarTabla);
            this.Controls.Add(this.btngenerar);
            this.Controls.Add(this.lbltitulo);
            this.Controls.Add(this.lbltextoinfo);
            this.Controls.Add(this.dgvlistado);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvlistado)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvlistado;
        private System.Windows.Forms.Label lbltextoinfo;
        private System.Windows.Forms.Label lbltitulo;
        private System.Windows.Forms.Button btngenerar;
        private System.Windows.Forms.Button btnactualizarTabla;
    }
}

