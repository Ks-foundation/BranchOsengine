import tkinter as tk

class RoundButton(tk.Canvas):
    def __init__(self, master=None, **kwargs):
        super().__init__(master, **kwargs)
        self.bind("<Button-1>", self._on_click)
        self._create_round_button()

    def _create_round_button(self):
        width = self.winfo_reqwidth()
        height = self.winfo_reqheight()
        self.create_oval(0, 0, width, height, fill='lightblue', outline='black', width=2)
        self.create_text(width/2, height/2, text="Click Me", fill="black", font=("Helvetica", 12, "bold"))

    def _on_click(self, event):
        print("Button clicked!")

# 예제 사용법
if __name__ == "__main__":
    root = tk.Tk()
    root.title("Round Button Example")
    
    round_button = RoundButton(root, width=100, height=40)
    round_button.pack(padx=20, pady=20)
    
    root.mainloop()
