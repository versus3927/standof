package com.femboy.strike

import android.app.Activity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import java.io.*

class MainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val btn = Button(this).apply {
            text = "ЗАПУСТИТЬ МАГИЮ, НЯ! ✨"
        }
        setContentView(btn)

        btn.setOnClickListener {
            try {
                val process = Runtime.getRuntime().exec("su")
                val os = DataOutputStream(process.outputStream)
                os.writeBytes("chmod 777 /data/local/tmp/libfemboy_strike.so\n")
                os.writeBytes("/data/local/tmp/libfemboy_strike.so &\n")
                os.writeBytes("exit\n")
                os.flush()
                Toast.makeText(this, "Elite-демон запущен! Доминируй! ✨", Toast.LENGTH_LONG).show()
            } catch (e: Exception) {
                Toast.makeText(this, "Ошибка Root: ${e.message}", Toast.LENGTH_LONG).show()
            }
        }
    }
}
