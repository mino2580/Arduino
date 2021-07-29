function varargout = vykreslovanie_teploty(varargin)
% Last Modified by GUIDE v2.5 01-Apr-2021 20:15:50
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @vykreslovanie_teploty_OpeningFcn, ...
                   'gui_OutputFcn',  @vykreslovanie_teploty_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before vykreslovanie_teploty is made visible.
function vykreslovanie_teploty_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;
guidata(hObject, handles);


% --- Outputs from this function are returned to the command line.
function varargout = vykreslovanie_teploty_OutputFcn(hObject, eventdata, handles) 
varargout{1} = handles.output;
clear all;
clc;
global a;
a=serial('COM3','BAUD', 9600); % Make sure the baud rate and COM port is
fopen(a);



% --- Executes on button press in pushbutton_On.
function pushbutton_On_Callback(hObject, eventdata, handles)
global a hodnota2;
x = 0;
S = 'Namerana teplota';
go = true;
hodnota= get(hObject,'value') 
i=0;
if hodnota==1

    while go
        
sizeA=[1,1];
temp=fscanf(a,'%f',sizeA);
set(handles.edit1_text,'String',num2str(temp));
disp(S)
disp(temp)
x = [x temp];
plot(handles.axes1,x);
grid on;
xlabel('Time(seconds)')
ylabel('Temperature(°C)');
title('Real-Time Temperature Graph');
drawnow
i=i+2;

NewName = {hodnota2 };
NewValues = [temp];
cas=[i];

% Check if you have created an Excel file previously or not 
checkforfile=exist(strcat(pwd,'\','ExcelFile.xls'),'file');
   if checkforfile==0; % if not create new one
    header = {'Nastavena C','Aktualna C','cas [s]'};
    xlswrite('ExcelFile',header,'Sheetname','A1');
    N=0;
   else % if yes, count the number of previous inputs
    N=size(xlsread('ExcelFile','Sheetname'),1);
   end
% add the new values (your input) to the end of Excel file

AA=strcat('A',num2str(N+2));
BB=strcat('B',num2str(N+2));
CC=strcat('C',num2str(N+2));
xlswrite('ExcelFile',NewName,'Sheetname',AA);
xlswrite('ExcelFile',NewValues,'Sheetname',BB);
xlswrite('ExcelFile',cas,'Sheetname',CC);
 





    end

end

 

function edit1_text_Callback(hObject, eventdata, handles)
% Hints: get(hObject,'String') returns contents of edit1_text as text
%        str2double(get(hObject,'String')) returns contents of edit1_text as a double


% --- Executes during object creation, after setting all properties.
function edit1_text_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_Off.
function pushbutton_Off_Callback(hObject, eventdata, handles)
global a;
hodnota= get(hObject,'value') 

S = 'Koniec';
disp(S)
fclose(a);
delete(a);




function edit2_zadaj_teplotu_Callback(hObject, eventdata, handles)
% Hints: get(hObject,'String') returns contents of edit2_zadaj_teplotu as text
%        str2double(get(hObject,'String')) returns contents of edit2_zadaj_teplotu as a double
global a hodnota2;
hodnota2=str2double(get(hObject,'String')) ;
S = 'Zadana teplota';
disp(S)
disp(hodnota2)
fprintf(a,'%i',hodnota2);



% --- Executes during object creation, after setting all properties.
function edit2_zadaj_teplotu_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
