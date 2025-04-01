# PROIECT-CN

## Simularea unei masini [Oprita /Serial]:

1.	Se vor folosi patru fotorezistente pentru starea usilor, doua leduri albe pentru faruri, un potentiometru pentru starea motorului, o fotorezistenta pentru farurile automat, un senzor PIR pentru detectarea miscarii in masina si un buzzer pentru alarma.
a.	Cand luminile sunt in modul “AUTO” iar masina este in accessories sau modul pornit se aprind farurile. Daca luminile sunt in modul “AUTO” iar masina este in modul oprit, atunci farurile se sting automat la intrarea in modul oprit. Pe serial monitor se face update “Light Status” cu auto in acest mod de operare.
b.	Daca motorul este oprit si status luminilor este auto, luminile se vor inchide automat iar pe serial monitor ramane valoarea “auto” la “Light Status”.
c.	Daca luminile sunt in modul “AUTO” si masina este in “ACC” sau “ON”, luminile se vor aprinde doar cand valoarea fotorezistentei este peste o valoare aleasa in stadiul de testare.
d.	Cand unul din fotorezistentele de pe masina pentru simularea usilor este sub/peste o valoare, statusul usii care este deschisa/inchisa isi face update sub “Door status” la usa respective cu “Closed” sau 
“Open”.
e.	Cand potentiometrul este 0-30% atunci motorul este “oprit”, cand potentiometrul este 31-60% atunci masina este in modul “accesorii”, cand potentiometrul este 61-100% atunci masina este cu motorul “pornit”.
f.	In functie de statusul motorului se face update la “Ignition Status” pe serial monitor cu “OFF”, “ON” sau “ACC”.
g.	Cand se trimite de pe serial monitor caracterul “L” masina are statusul ca “Locked” iar prin trimiterea caracterului “U” masina are statusul ca “Unlocked”. Se va face update la “Lock Status” in functie de ce character a fost trimis pe serial monitor.
h.	Cand masina este “Locked” ledul rosu se va aprinde si stinge cu o latent de 1 secunda, iar cand masina este “Unlocked”, ledul este stins.
i.	Masina isi va da lock doar daca motorul este oprit si toate usile sunt inchise (valoarea “Closed” la toate usile si “Ignition Status: Off”).
j.	Prin trimiterea caracterului “A” pe serial monitor farurile sunt in modul “auto” si se va updata “Light Status” cu “auto”.
k.	Prin trimiterea caracterului “O” farurile sunt oprite si “Light Status” este updatat cu “Off”.
l.	Prin trimiterea caracterului “P” farurile sunt pornite si “Light Status” este updatat cu “On”.
m.	Senzorul PIR este active doar cand masina este in starea de “Lock Status: Locked”.
n.	Cand exista miscare in masina in timp ce senzorul este activ, farurile se aprind si sting cu o latenta de 1 secunda, iar buzzerul se aprinde si stinge tot cu o latenta de 1 secunda, acest mod de alarma tine 10 secunde.
o.	Serial monitor este updatat periodic dar nu foarte rar pentru a avea statusul curent al masinii cat mai precis.
p.	Daca o usa se deschide cand masina este “Locked”, masina va deveni “Unlocked” iar senzorul PIR va fi dezactivat, de asemenea si alarma va fi dezactivata daca a fost activata inainte.
q.	Cand masina are motorul oprit si farurile pornite (ON, nu auto), la deschiderea oricarei usi buzzerul va incepe sa sune pana la inchiderea usii/usilor deschise.
r.	Masina poate intra in modul “locked” chiar daca usile din spate sunt deschise, dar verificarea miscarii in masina cu senzorul PIR va incepe doar atunci cand toate usile au fost inchise.

 
