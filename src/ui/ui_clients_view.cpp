#include "imgui.h"
#include "ui.h"

#include "core/base.h"
#include "core/string.h"
#include "core/uuid.h"

#include <algorithm>
#include <string>

struct Client {
  u32    id;
  bool32 is_legal;

  string name;
  string legal_name;
  string phono_number;
  string address;
  string legal_address;
  string actual_address;
  string email;
  string note;
  string counterparty;
  string data;
  string mark;
  string source;
};

const char *names_template[] = {
  "Максимов Максим Максимович",          "Михайлов Михаил Михайлович",
  "Александров Александр Александрович", "Денисов Денис Денисович",
  "Дмитриев Дмитрий Дмитриевич",
};
const char *phone_numbers_template[] = {
  "+7 123 456-78-90", "+7 987 654-32-10", "+7 555 555-55-55",
  "+7 111 222-33-44", "+7 999 888-77-66",
};
const char *addresses_template[] = {
  "ул. Ленина, д. 1, г. Москва, 123456",
  "пр. Победы, д. 10, г. Санкт-Петербург, 654321",
  "ул. Профсоюзная, д. 20, г. Екатеринбург, 987654",
  "пер. Гагарина, д. 5, г. Новосибирск, 456789",
  "ул. Красная, д. 15, г. Казань, 789654",
};
const char *email_addresses_template[] = {
  "example1@mail.ru",    "example2@gmail.com", "example3@yandex.ru",
  "example4@rambler.ru", "example5@inbox.ru",
};
const char *dates_template[]
    = { "01-01-2020", "15-03-2021", "10-07-2022", "05-11-2023", "30-09-2024" };

void
ui_clients_view_show(void)
{
  static Client client[5];
  static bool32 is_init_client;
  if (!is_init_client) {
    is_init_client = true;
    for (u32 i = 0; i < ArrayCount(client); i++) {
      client[i] = {
        .id           = i + 1,
        .is_legal     = false,
        .name         = str_lit(names_template[i]),
        .phono_number = str_lit(phone_numbers_template[i]),
        .address      = str_lit(addresses_template[i]),
        .email        = str_lit(email_addresses_template[i]),
        .note         = str_lit("Test"),
        .counterparty = str_lit("Test"),
        .data         = str_lit(dates_template[i]),
        .mark         = str_lit("VIP"),
        .source       = str_lit("Test"),
      };
    }
  }

  ImGui::Text("Клиенты");

  if (ImGui::Button("Добавить")) {
    ImGui::OpenPopup("Добавление клиента");
  }
  ImGui::SameLine();
  ImGui::Button("Удалить");

  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

  if (ImGui::BeginPopupModal("Добавление клиента", NULL,
                             ImGuiWindowFlags_NoMove
                                 | ImGuiWindowFlags_AlwaysAutoResize)) {
    static bool is_valid        = false;
    static bool is_organization = false;

    ImGui::Checkbox("Организация", &is_organization);

    if (!is_organization) {

      static char input_name[1024] = "";
      ImGui::InputText("Ф.И.О", input_name, ArrayCount(input_name));
    } else {
      static char input_name[1024] = "";
      ImGui::InputText("Название организации", input_name,
                       ArrayCount(input_name));
    }

    // InputPhone
    {
      // +7 000 000-00-00
      static char input_phone[1024] = "";

      ImGui::InputText("Телефон", input_phone, ArrayCount(input_phone),
                       ImGuiInputTextFlags_CharsDecimal);

      // strcpy(input_phone, "+7 ");
      // sprintf(input_buffer, "%s", input_phone);
      // sprintf(input_phone, "+7 %s", input_buffer);
    }

    if (!is_organization) {
      static char input_address[1024] = "";
      ImGui::InputText("Адрес", input_address, ArrayCount(input_address));
    } else {
      static char input_legal_address[1024] = "";
      ImGui::InputText("Юридический адрес", input_legal_address,
                       ArrayCount(input_legal_address));

      static char input_actual_address[1024] = "";
      ImGui::InputText("Фактический адрес", input_actual_address,
                       ArrayCount(input_actual_address));
    }

    static char input_email[1024] = "";
    ImGui::InputText("Эл. почта", input_email, ArrayCount(input_email));

    static char input_note[1024] = "";
    ImGui::InputText("Примечание", input_note, ArrayCount(input_note));

    // Контрагент
    {
      static const char *items[] = {
        "Не выбран",
        "Иванов Иван Иванович",
        "Петров Петр Петрович",
        "Сидоров Алексей Владимирович",
        "Смирнов Михаил Николаевич",
      };
      static u32  item_current_idx = 0;
      const char *preview_value    = items[item_current_idx];

      if (ImGui::BeginCombo("Контрагент", preview_value, 0)) {
        for (size_t i = 0; i < ArrayCount(items); i++) {
          const u32 is_selected = (item_current_idx == i);
          if (ImGui::Selectable(items[i], is_selected)) {
            item_current_idx = i;
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }
    }

    // Статус клиента(метка)
    {
      static const char *items[] = {
        "Не выбран", "-5%",    "-10%",       "-20%", "-30%",
        "Забанен",   "Скидка", "Постоянный", "VIP",
      };
      static u32  item_current_idx = 0;
      const char *preview_value    = items[item_current_idx];

      if (ImGui::BeginCombo("Статус клиента(метка)", preview_value, 0)) {
        for (size_t i = 0; i < ArrayCount(items); i++) {
          const u32 is_selected = (item_current_idx == i);
          if (ImGui::Selectable(items[i], is_selected)) {
            item_current_idx = i;
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }
    }

    // Рекламный канал(источник)
    {
      static const char *items[] = {
        "Не определен",       "Интернет",         "Партнер", "По рекомендации",
        "Постоянные клиенты", "Проходящий поток", "СЦ ТРУД",
      };
      static u32  item_current_idx = 0;
      const char *preview_value    = items[item_current_idx];

      if (ImGui::BeginCombo("Рекламный канал(источник):", preview_value, 0)) {
        for (size_t i = 0; i < ArrayCount(items); i++) {
          const u32 is_selected = (item_current_idx == i);
          if (ImGui::Selectable(items[i], is_selected)) {
            item_current_idx = i;
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }
    }

    if (ImGui::Button("OK", ImVec2(120, 0)) && is_valid) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }

  const float TEXT_BASE_WIDTH  = ImGui::CalcTextSize("A").x;
  const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
  const char *items_clip_max[] = {
    "1", "5", "10", "20", "50", "100",
  };
  static int  item_current_idx = 0;
  const char *preview_value    = items_clip_max[item_current_idx];
  u32         max_client_view  = strtol(preview_value, NULL, 10);

  if (ImGui::BeginTable("table_clients", 6,
                        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg
                            | ImGuiTableFlags_ScrollY
                            | ImGuiTableFlags_Sortable
                            | ImGuiTableFlags_Resizable,
                        ImVec2(0.0f, TEXT_BASE_HEIGHT * 40), 0.0f)) {
    ImGui::TableSetupColumn("ID");
    ImGui::TableSetupColumn("Ф.И.О");
    ImGui::TableSetupColumn("Телефон");
    ImGui::TableSetupColumn("Адрес");
    ImGui::TableSetupColumn("Эл.почта");
    ImGui::TableSetupColumn("Дата регистрации");
    ImGui::TableHeadersRow();

    ImGuiListClipper clipper;
    clipper.Begin(ClampTop(ArrayCount(client), max_client_view));

    while (clipper.Step())
      for (u32 row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd;
           row_n++) {
        if (row_n < max_client_view) {
          ImGui::PushID(row_n);
          ImGui::TableNextRow();

          ImGui::TableNextColumn();
          ImGui::Text("%04d", client[row_n].id);

          ImGui::TableNextColumn();
          ImGui::TextUnformatted(client[row_n].name.str);

          ImGui::TableNextColumn();
          ImGui::TextUnformatted(client[row_n].phono_number.str);

          ImGui::TableNextColumn();
          ImGui::TextUnformatted(client[row_n].address.str);

          ImGui::TableNextColumn();
          ImGui::TextUnformatted(client[row_n].email.str);

          ImGui::TableNextColumn();
          ImGui::TextUnformatted(client[row_n].data.str);

          ImGui::PopID();
        }
      }

    ImGui::EndTable();
  }

  {
    static ImVec2 combo_padding = ImVec2(14, 14);

    ImGui::SetNextItemWidth(100);
    if (ImGui::BeginCombo("##combo", preview_value, 0)) {
      for (int n = 0; n < IM_ARRAYSIZE(items_clip_max); n++) {
        const bool is_selected = (item_current_idx == n);
        if (ImGui::Selectable(items_clip_max[n], is_selected)) {
          item_current_idx = n;
        }
        if (is_selected) {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
  }
}
